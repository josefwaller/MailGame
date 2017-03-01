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
		
		print(self.data)
		
		# makes all objects unrenderable
		for o in list(bpy.data.objects):
			o.hide_render = True
		
		for o in self.data:
			self.render_object(o)
			
	def read_data_file(self):
		
		file = open("model_data.json", "r")
		
		return json.loads(file.read())
		
	def render_object(self, objectKey):
	
		# sets camera resolution
		res = bpy.context.scene.render
		if "camera_res" in self.data[objectKey]:	
		
			res.resolution_x = getIfExists(self.data[objectKey]['camera_res'], 'x', 64)		
			res.resolution_y = getIfExists(self.data[objectKey]['camera_res'], 'y', 64)		
			
		else:
			res.resolution_x = 64
			res.resolution_y = 64
		
		objData = self.data[objectKey]
		
		default = {
			"x": 0,
			"y": 0,
			"z": 0
		}
	
		if "path" in objData:
		
			path = self.data[objectKey]['path']
		
			pos = getIfExists(objData, "pos", default)
		
			rot = getIfExists(objData, "rot", default)
		
			scale = getIfExists(objData, "scale", default)
				
			self.setObjAttributes(objectKey, pos, rot, scale)
			self.render_sprite(objectKey, path)
			
		elif "paths" in objData:
		
			path_prefix = objData['path_prefix']
		
			for i in range(len(objData['paths'])):	
				
				path = path_prefix + objData['paths'][i]
				
				rot = default.copy()
				pos = default.copy()
				scale = default.copy()
				
				for axis in ["x", "y", "z"]:
				
					rot[axis] = getAxisValue(objData, "rot", axis, i)
					pos[axis] = getAxisValue(objData, "pos", axis, i)
					scale[axis] = getAxisValue(objData, "scale", axis, i)
					
				print(pos)
				self.setObjAttributes(objectKey, pos, rot, scale)
				self.render_sprite(objectKey, path)
	
	def setObjAttributes(self, objectKey, pos, rot, scale):
	
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
		
	def render_sprite(self, objectKey, path):
		
		object = bpy.data.objects[objectKey]
		
		# sets to render
		object.hide_render = False
		
		# gets the path to render the image to
		dirname = os.path.dirname
		assets_path = dirname(dirname(__file__)) + "\\MailGame\\assets\\sprites\\" + path
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