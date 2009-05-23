#!BPY

# ---------------------------------------------------------------------------- #

"""
Name: 'Playground Mesh (.pme)...'
Blender: 248
Group: 'Export'
Tooltip: 'Export a Playground PME file'
"""

# ---------------------------------------------------------------------------- #

__author__ = ("Mike Kasprzak")
__url__ = ["Sykhronics Entertainment, http://www.sykhronics.com",
"Mike's Blog, http://www.toonormal.com"]
__version__ = "0.1 (2009-05-22)"

# ---------------------------------------------------------------------------- #

__bpydoc__ = """\
This script exports PME files, usable in games developed by/with Sykhronics Entertainment.

Usage:

Run this script from "File->Export" menu.
"""

# ---------------------------------------------------------------------------- #

import Blender
from Blender import sys as bsys
from Blender import Mathutils
from Blender import Lamp
from Blender import Camera
from Blender import Window
import math

# Utility Library, soon to become standardized (BPy is new API) #
import BPyMesh

# ---------------------------------------------------------------------------- #
# Global Vars #
SCN = []		# Current Scene #
EXPORT_DIR = ''	# Export Directory #
# ---------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------- #
def write_facemesh( FP, mesh ):
	quadrange = [0, 1, 2, 1, 2, 3]
	
	FP.write( 'Mesh\n' )
	for face in mesh.faces:
		idxrange = range(len(face.verts))
		
		if len(face.verts) == 4:
			idxrange = quadrange
			
		FP.write('	Face\n')
		for idx in idxrange:
			v = face.verts[idx]
			
			FP.write( '		Vertex' )
			FP.write( 'Norm' )
			if mesh.faceUV:
				FP.write( 'UV' )
			if mesh.vertexColors:
				FP.write( 'Color' )
			
			FP.write( ' %.6f %.6f %.6f' % tuple(v.co) )
			FP.write( '  %.6f %.6f %.6f' % tuple(v.no) )
			if mesh.faceUV:
				FP.write( '  %.6f %.6f' % tuple(face.uv[idx]) )
			if mesh.vertexColors:
				FP.write( '  %i %i %i %i' % (face.col[idx].r, face.col[idx].a, face.col[idx].b, face.col[idx].a) )
			FP.write( '\n' )
# ---------------------------------------------------------------------------- #
def write_mesh( FP, mesh ):
	quadrange = [0, 1, 2, 1, 2, 3]
	
	FP.write( 'Mesh\n' )
	FP.write( '	Materials\n' )
	
	for idx in range(len(mesh.materials)):
		material = mesh.materials[idx]
		FP.write( '		Material %i\n' % idx )
		for mytex in material.getTextures():
			if mytex:
				if mytex.tex.getType() == 'Image':
					FP.write( '			Image \"%s\"\n' % mytex.tex.getImage().getName() )
				else:
					FP.write( '			// Empty Material //\n' )
				
	FP.write( '	Vertices\n' )
	for face in mesh.faces:
		for idx in range(len(face.verts)):
			v = face.verts[idx]
			
			FP.write( '		Vertex' )
			FP.write( 'Norm' )
			if mesh.faceUV:
				FP.write( 'UV' )
			if mesh.vertexColors:
				FP.write( 'Color' )
			
			FP.write( ' %.6f %.6f %.6f' % tuple(v.co) )
			if face.smooth:
				FP.write( '  %.6f %.6f %.6f' % tuple(v.no) )
			else:
				FP.write( '  %.6f %.6f %.6f' % tuple(face.no) )
			if mesh.faceUV:
				FP.write( '  %.6f %.6f' % tuple(face.uv[idx]) )
			if mesh.vertexColors:
				FP.write( '  %i %i %i %i' % (face.col[idx].r, face.col[idx].a, face.col[idx].b, face.col[idx].a) )
			FP.write( '\n' )

	FP.write( '	Faces\n' )
	for idx in range(len(mesh.materials)):
		material = mesh.materials[idx]
		FP.write( '		UseMaterial %i\n' % idx )
		vert = 0
		for face in mesh.faces:
			if face.mat == idx:
				if len(face.verts) == 3:
					FP.write( '			Face %i %i %i\n' % (vert+0,vert+1,vert+2) )
				elif len(face.verts) == 4:
					FP.write( '			Face %i %i %i\n' % (vert+0,vert+1,vert+2) )
					FP.write( '			Face %i %i %i\n' % (vert+1,vert+2,vert+3) )
				
			vert += len(face.verts)
	FP.write( '\n' )
# ---------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------- #
def write_pme(filename):
	global EXPORT_DIR
	
	# Note the start time of this operation, so we can log how long this took #
	StartTime = Blender.sys.time()
	
	# Append ".pme" in case it's missing it #
	if not filename.lower().endswith('.pme'):
		filename += '.pme'

	# 
	export_dir = bsys.dirname(filename)
	if export_dir != EXPORT_DIR:
		EXPORT_DIR = export_dir

	# If I'm in Edit Mode, Change out of it #	
	in_editmode = Window.EditMode()
	if in_editmode:
		Window.EditMode(0)

	# Get the current scene #	
	SCN = Blender.Scene.GetCurrent()
	
	# Open the File #
	file = open( filename, 'wb' )
	
	# Export Data #
	for obj in SCN.objects:
		#print 'Obj %s' % ( obj.getType() )	
		if 'Mesh' == obj.type:
			# getMeshFromObject( Object, Parent, Apply Modifiers, VGroup?, Scene ) #
			mesh = BPyMesh.getMeshFromObject(obj, None, True, False, SCN)
#			mesh.transform(obj.matrixWorld)
			write_mesh( file, mesh )
		
	file.close()
				
#	if not mesh:
#		Blender.Draw.PupMenu('Error%t|Could not get mesh data from active object')
#		return
	
	# If we were in edit mode, restore it #
	if in_editmode:
		Window.EditMode(1)
	
	# Completed - Log the time it took #
	EndTime = Blender.sys.time()
	message = 'Successfully exported "%s" in %.4f seconds' % ( Blender.sys.basename(filename), EndTime-StartTime)
	print message


def main():
	fname = bsys.makename(ext=".pme")
	if EXPORT_DIR <> '':
		fname = bsys.join( EXPORT_DIR, bsys.basename(fname) )

	Blender.Window.FileSelector( write_pme, 'PME Export', fname )


if __name__=='__main__':
	main()

