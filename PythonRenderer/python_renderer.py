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
		
		for i in range(len(self.data[objectKey])):
			self.render_sprite(objectKey, i)
		
	def render_sprite(self, objectKey, index):
		
		object = bpy.data.objects[objectKey]
		
		objData = self.data[objectKey][index]
		
		# sets position
		if "pos" in objData:
			position = objData['pos']
			object.location = Vector((
				position['x'],
				position['y'],
				position['z']
			))
			
		else:
			object.location = Vector((0, 0, 0));
		
		# sets rotation
		if "rot" in objData:
		
			x = 0
			y = 0
			z = 0
			
			if "x" in objData['rot']:
				x = objData['rot']['x']
				
			if "y" in objData['rot']:
				y = objData['rot']['y']
				
			if "z" in objData['rot']:
				z = objData['rot']['z']
				
			object.rotation_euler = Vector((
				radians(x), 
				radians(y),
				radians(z)))
		
		# sets scale
		
		# sets to render
		object.hide_render = False
		
		# gets the path to render the image to
		dirname = os.path.dirname
		assets_path = dirname(dirname(__file__)) + "\\MailGame\\assets\\sprites\\" + objData["path"]
		print(assets_path)
		
		bpy.data.scenes["Scene"].render.filepath = assets_path
		stat = bpy.ops.render.render(write_still=True)
		
		object.hide_render = True
		
		print(stat)