bl_info = {
    "name": "Pyd Example",
    "author": "bd3d",
    "version": (1, 0),
    "blender": (3, 40, 0),
    "location": "",
    "description": "Source files and demos on creating your own .pyd",
    "warning": "",
    "category": "",
}

import bpy

from . import pydll

class PYD_PR_Test(bpy.types.PropertyGroup):

    def test(self, a:int,b:int):
        r = pydll.simpleadd.add(a, b)
        return r

def register():
    bpy.utils.register_class(PYD_PR_Test)
    bpy.types.Object.pydtest = bpy.props.PointerProperty(type=PYD_PR_Test)


def unregister():
    del bpy.types.Object.pydtest
    bpy.utils.unregister_class(PYD_PR_Test)