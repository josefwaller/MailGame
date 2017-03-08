import bpy
import json
from mathutils import Vector
from math import radians
import os

class PythonRenderer:

	def __init__(self):
		
		# Reads the data for each object which needs to be rendered
		# contains things like rotation, position, etc
		self.data = self.read_data_file()
		
		# makes all objects unrenderable
		for o in list(bpy.data.objects):
			o.hide_render = True
			
	def read_data_file(self):

		file = open(os.path.dirname(bpy.data.filepath) + "\\model_data.json", "r")
		
		return json.loads(file.read())

	def render_all(self):
		for o in self.data:
			self.render_object(o)
		
	def render_object(self, objectKey):

		if objectKey not in self.data:
			print("%s is not in data!" % objectKey)
			return
		
		# this object's data on how it should be rendered, taken frm the file
		objData = self.data[objectKey]
		
		# an array of different setups for rendering the object
		# each entry is a different sprite to be rendered
		renderDatas = []

		# sets camera resolution
		res = bpy.context.scene.render
		if "camera_res" in self.data[objectKey]:	
		
			res.resolution_x = getIfExists(self.data[objectKey]['camera_res'], 'x', 64)		
			res.resolution_y = getIfExists(self.data[objectKey]['camera_res'], 'y', 64)		
			
		else:
			res.resolution_x = 64
			res.resolution_y = 64

		# sets anti-aliasing
		bpy.data.scenes["Scene"].render.use_antialiasing = getIfExists(objData, "aa", True)
		
		default = {
			"x": 0,
			"y": 0,
			"z": 0
		}
	
		if "path" in objData:
		
			renderData = {
				"path": self.data[objectKey]['path'],
				"pos": getIfExists(objData, "pos", default),
				"rot": getIfExists(objData, "rot", default),
				"scale": getIfExists(objData, "scale", default),
				"texture": None
			}
			
			renderDatas.append(renderData)
			
		elif "paths" in objData:
		
			path_prefix = objData['path_prefix']
		
			for i in range(len(objData['paths'])):	
				
				renderData = {
					"path": path_prefix + objData['paths'][i],
					"rot": default.copy(),
					"pos": default.copy(),
					"scale": default.copy()
				}
				
				for axis in ["x", "y", "z"]:
				
					renderData["rot"][axis] = getAxisValue(objData, "rot", axis, i)
					renderData["pos"][axis] = getAxisValue(objData, "pos", axis, i)
					renderData["scale"][axis] = getAxisValue(objData, "scale", axis, i)
					
				if "textures" in objData:
				
					for t in objData["textures"]:
					
						textureData = renderData.copy()
						
						textureData["texture"] = objData["texture_prefix"] + t
						
						textureData["path"] += "_" + t
						
						renderDatas.append(textureData)
					
				else:
					renderData["texture"] = None
					
					renderDatas.append(renderData)
					
		for renderData in renderDatas:
		
			self.setObjAttributes(objectKey,
				renderData["pos"],
				renderData["rot"],
				renderData["scale"],
				renderData["texture"])
				
			self.render_sprite(objectKey, 
				renderData["path"])
	
	def setObjAttributes(self, objectKey, pos, rot, scale, texture=None):
	
		object = bpy.data.objects[objectKey]
		
		# sets position
		object.location = Vector((
			pos['x'],
			pos['y'],
			pos['z']
		))
		
		# sets rotation
		object.rotation_euler = Vector((
			radians(rot['x']), 
			radians(rot['y']),
			radians(rot['z'])))
		
		# sets scale
		
		# sets texture
		if texture != None:
		
			# gets the material with a texture
			for m in object.material_slots:
				
				if m.material.active_texture != None:
				
					i = bpy.data.images.load(
						os.path.dirname(bpy.data.filepath) + 
						"/textures/" + texture + ".png")
					
					m.material.active_texture.image = i
		
	def render_sprite(self, objectKey, path):
		
		object = bpy.data.objects[objectKey]
		
		# sets to render
		object.hide_render = False
		
		# gets the path to render the image to
		dirname = os.path.dirname
		assets_path = dirname(dirname(bpy.data.filepath)) + "\\MailGame\\assets\\sprites\\" + path
		print(assets_path)
		
		bpy.data.scenes["Scene"].render.filepath = assets_path
		stat = bpy.ops.render.render(write_still=True)
		
		object.hide_render = True
		
		print(stat)
		
def getAxisValue (dict, key, axis, index):	
				
	if key in dict:
		if axis in dict[key]:
			return dict[key][axis][index]
			
	return 0
		
def getIfExists(dict, key, alt):
	
	if key in dict:
		return dict[key]
		
	else:
		return alt

if __name__ == "__main__":
	p = PythonRenderer()

	allObjs = []

	while True:
		print("EXIT - cancels")
		print("RENDER - Renders all given objects")
		print("UNDO - removes the last object entered")
		print("ALL - Renders all objects and ends the session")
		obj = input("Enter the object you want to enter, or a specail character: ")

		if obj == "EXIT":
			break

		elif obj == "UNDO":
			allObjs.pop(-1)

		elif obj == "RENDER":
			
			for o in allObjs:
				p.render_object(o)

			break

		elif obj == "ALL":
			p.render_all()
			break

		else:
			allObjs.append(obj)