#include "Chunk.h"

#define _normal_up     0 // y++
#define _normal_down   1 // y--
#define _normal_north  2 // x++
#define _normal_south  3 // x--
#define _normal_east   4 // z++
#define _normal_west   5 // z--

// Get block type macro
#define _get(x, y, z)\
blocks[\
    _clamp(x, this->sizeX) + \
    _clamp(y, this->sizeY) * this->sizeX + \
    _clamp(z, this->sizeZ) * this->sizeX * this->sizeY\
]

// Get lightvol macro
#define _getlv(x, y, z)\
(x < 0 || y < 0 || z < 0 || x >= sizeX || y >= sizeY || z >= sizeZ) ? 255 : \
lightvol[\
    _clamp(x, this->sizeX) + \
    _clamp(y, this->sizeY) * this->sizeX + \
    _clamp(z, this->sizeZ) * this->sizeX * this->sizeY\
]

// Set block type macro
#define _put(x, y, z, value)\
blocks[\
    _clamp(x, this->sizeX) + \
    _clamp(y, this->sizeY) * this->sizeX + \
    _clamp(z, this->sizeZ) * this->sizeX * this->sizeY\
] = value

// Set lightvol macro
#define _putlv(x, y, z, value)\
lightvol[\
    _clamp(x, this->sizeX) + \
    _clamp(y, this->sizeY) * this->sizeX + \
    _clamp(z, this->sizeZ) * this->sizeX * this->sizeY\
] = value

// For pushing verticies onto the buffer in Chunk::compute()
#define _vertex(x,y,z,color,light,normal)\
buffer[s++] = x;        buffer[s++] = y;        buffer[s++] = z;\
buffer[s++] = color->r; buffer[s++] = color->g; buffer[s++] = color->b;\
buffer[s++] = light;    buffer[s++] = normal;   t++;

inline int _clamp(int v, int max)
{
    if (v < 0) return 0;
    if (v > max) return max;
    return v;
}

Chunk::Chunk(Tileset* tileset, int sizeX, int sizeY, int sizeZ)
{
    this->tileset = tileset;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->sizeZ = sizeZ;
    changed = true;
    triangles = 0;
    blocks = (byte*)calloc(sizeX * sizeY * sizeZ, 1);
    if (blocks == NULL)
    {
        printf("Chunk malloc failed\n");
        exit(2);
    }

    position = vec3(0,0,0);
    model = glm::translate(mat4(1.0f), position);
    geometry = new VoxelObject();

    for(byte z = 0; z < this->sizeZ; z++)
    {
        //for(byte y = 0; y < this->sizeY; y++)
        {
            for(byte x = 0; x < this->sizeX; x++)
            {
                _put(x,0,z,rand() % 3 + 1);
            }
        }
    }

}

Chunk::~Chunk()
{
    free(this->blocks);
    delete geometry;
}

byte Chunk::get(int x, int y, int z)
{
    return _get(x,y,z);
}

void Chunk::set(int x, int y, int z, byte type)
{
    _put(x,y,z,type);
    changed=true;
}

vec3 Chunk::getPosition()
{
    return position;
}

void Chunk::setPosition(vec3 position)
{
    this->position = position;
    model = glm::translate(mat4(1.0f), position);
}

void Chunk::draw(VoxelShader* shader)
{
    shader->setUniformMatrix("model", &model);
    geometry->draw();
}

/**
 *  Computes vertex data and uploads to GPU
 */
void Chunk::compute()
{
    if (!changed) return;
    double startTime = glfwGetTime();
    int s = 0, t = 0;
    byte type = 0;

    int memsize = sizeX * sizeY * sizeZ * 36 * VOXELSH_VERTEX_SIZE;
    byte* buffer = (byte*)malloc(memsize);
    if (buffer == NULL)
    {
        printf("Chunk buffer malloc failed\n");
        exit(0);
    }

    byte* lightvol = (byte*)malloc(sizeX * sizeY * sizeZ);
    for(int z = 0; z < sizeZ; z++)
    {
        for(int y = 0; y < sizeY; y++)
        {
            for(int x = 0; x < sizeX; x++)
            {
                int type = _get(x,y,z);
                if (type != 0)
                {
                    // Filled blocks have 0 light
                    _putlv(x,y,z,0);
                    continue;
                }
                byte lightlv = 0;
                if ((x+1 >= sizeX) || _get(x+1,y,z) == 0) lightlv++;
                if ((x-1 < 0) || _get(x-1,y,z) == 0) lightlv++;
                if ((y+1 >= sizeY) || _get(x,y+1,z) == 0) lightlv++;
                if ((y-1 < 0) || _get(x,y-1,z) == 0) lightlv++;
                if ((z+1 >= sizeZ) || _get(x,y,z+1) == 0) lightlv++;
                if ((z-1 < 0) || _get(x,y,z-1) == 0) lightlv++;
                lightlv = lightlv * 255/6;
                _putlv(x,y,z,lightlv);
            }
        }
    }

    for(int z = 0; z < sizeZ; z++)
    {
        for(int y = 0; y < sizeY; y++)
        {
            for(int x = 0; x < sizeX; x++)
            {
                type = _get(x,y,z);
                if (type == 0)
                    continue;

                Color* color;
                color = tileset->get(type);
                byte light = 255;
                
                // North (x+)
                if ((x+1 >= sizeX) || _get(x+1,y,z) == 0)
                {
                    light = _getlv(x+1,y,z);
                    _vertex(x+1, y+1, z+0, color, light, _normal_north)
                    _vertex(x+1, y+0, z+1, color, light, _normal_north)
                    _vertex(x+1, y+0, z+0, color, light, _normal_north)

                    _vertex(x+1, y+1, z+1, color, light, _normal_north)
                    _vertex(x+1, y+0, z+1, color, light, _normal_north)
                    _vertex(x+1, y+1, z+0, color, light, _normal_north)
                }
                
                // South (x-)
                if ((x-1 < 0) || _get(x-1,y,z) == 0)
                {
                    light = _getlv(x-1,y,z);
                    _vertex(x+0, y+0, z+0, color, light, _normal_south)
                    _vertex(x+0, y+0, z+1, color, light, _normal_south)
                    _vertex(x+0, y+1, z+0, color, light, _normal_south)

                    _vertex(x+0, y+1, z+0, color, light, _normal_south)
                    _vertex(x+0, y+0, z+1, color, light, _normal_south)
                    _vertex(x+0, y+1, z+1, color, light, _normal_south)
                }
                
                // Up (y+)
                if ((y+1 >= sizeY) || _get(x,y+1,z) == 0)
                {
                    light = _getlv(1,y+1,z);
                    _vertex(x+0, y+1, z+1, color, light, _normal_up)
                    _vertex(x+1, y+1, z+0, color, light, _normal_up)
                    _vertex(x+0, y+1, z+0, color, light, _normal_up)
                    
                    _vertex(x+1, y+1, z+1, color, light, _normal_up)
                    _vertex(x+1, y+1, z+0, color, light, _normal_up)
                    _vertex(x+0, y+1, z+1, color, light, _normal_up)
                }

                // Down (y-)
                if ((y-1 < 0) || _get(x,y-1,z) == 0)
                {
                    light = _getlv(x,y-1,z);
                    _vertex(x+0, y+0, z+0, color, light, _normal_down)
                    _vertex(x+1, y+0, z+0, color, light, _normal_down)
                    _vertex(x+0, y+0, z+1, color, light, _normal_down)
                    
                    _vertex(x+0, y+0, z+1, color, light, _normal_down)
                    _vertex(x+1, y+0, z+0, color, light, _normal_down)
                    _vertex(x+1, y+0, z+1, color, light, _normal_down)
                }
                
                // East (z+)
                if ((z+1 >= sizeZ) || _get(x,y,z+1) == 0)
                {
                    light = _getlv(x,y,z+1);
                    _vertex(x+1, y+1, z+1, color, light, _normal_east)
                    _vertex(x+0, y+1, z+1, color, light, _normal_east)
                    _vertex(x+0, y+0, z+1, color, light, _normal_east)

                    _vertex(x+0, y+0, z+1, color, light, _normal_east)
                    _vertex(x+1, y+0, z+1, color, light, _normal_east)
                    _vertex(x+1, y+1, z+1, color, light, _normal_east)
                }
                
                // West (z-)
                if ((z-1 < 0) || _get(x,y,z-1) == 0)
                {
                    light = _getlv(x,y,z-1);
                    _vertex(x+0, y+0, z+0, color, light, _normal_west)
                    _vertex(x+0, y+1, z+0, color, light, _normal_west)
                    _vertex(x+1, y+1, z+0, color, light, _normal_west)

                    _vertex(x+1, y+1, z+0, color, light, _normal_west)
                    _vertex(x+1, y+0, z+0, color, light, _normal_west)
                    _vertex(x+0, y+0, z+0, color, light, _normal_west)
                }
            }
        }
    }

    changed = false;
    triangles = t;

    geometry->bufferData(buffer, t);
    free(buffer);
    free(lightvol);

    double elapsed = (glfwGetTime() - startTime) * 1000.0 + 0.5;
    printf("Chunk computed. %d triangles (%dkB) uploaded to GPU. Time: %dms\n", t, s / 1024, (int)(elapsed));
    
}