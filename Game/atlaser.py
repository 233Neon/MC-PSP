from PIL import Image
import sys
 

test_img = Image.open("assets/minecraft/textures/blocks/dirt.png")

size = test_img.size
test_img.close()

default_size = size[0]

#New image must be 24 * size by 24 * size

ROWS = 24
COLUMNS = 24

atlas = Image.new("RGBA", (ROWS * default_size, COLUMNS * default_size), 0)


# TEST FOR NOW, load from file later!
if len(sys.argv) - 1 == 0:
    fp = open("blocktex_list.txt", "r")
else:
    fp = open("itemtex_list.txt", "r")


line = fp.readline()

count = 0
while line:
    if len(sys.argv) - 1 == 0:
        atlas.paste(Image.open("assets/minecraft/textures/blocks/" + line.strip() + ".png") , (count * default_size, count // COLUMNS * default_size))
    else:
        atlas.paste(Image.open("assets/minecraft/textures/items/" + line.strip() + ".png") , (count * default_size, count // COLUMNS * default_size))
    line = fp.readline()
    count = count + 1

fp.close()

if len(sys.argv) - 1 == 0:
    atlas.save("assets/minecraft/textures/terrain_atlas.png", "PNG")
else:
    atlas.save("assets/minecraft/textures/items_atlas.png", "PNG")
