#include <Windows.h>
#include "framework.h"
#include "Space Arena.h"

#include "2x11.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <array> 

#include <iostream>

 
struct Particle
{
    D3DXVECTOR2 position;
    D3DXVECTOR2 velocity;
    float size;
    DWORD color;
    float life;  // Remaining life of the particle (in seconds)
};

struct Vertex
{
    float x, y, z;
};

IDirect3DVertexBuffer9* pVB = NULL;

const int NUM_PARTICLES = 100;
Particle particles[NUM_PARTICLES];



 
 
void Update(float deltaTime);
void DrawParticle(const Particle& particle);
void Renderparticle();
 
 
//extern const int X  ;
//extern const int Y  ;
extern LPDIRECT3DDEVICE9    g_pd3dDevice;
  

void Update(float deltaTime)
{
    for (int i = 0; i < NUM_PARTICLES; ++i)
    {
        particles[i].life -= deltaTime;
        if (particles[i].life > 0.0f)
        {
            particles[i].velocity.y += 9.8f * deltaTime;  // Gravity
            particles[i].position += particles[i].velocity * deltaTime;
            particles[i].size -= deltaTime;  // Decrease size over time
        }
        else
        {
            // Respawn particle when its life is over
            particles[i].position = D3DXVECTOR2(rand() % X, rand() % Y);
            particles[i].velocity = D3DXVECTOR2((rand() % 100 - 50) / 10.0f, (rand() % 100 - 50) / 10.0f);
            particles[i].size = 1.0f + static_cast<float>(rand() % 5);  // Random size
            particles[i].color = D3DCOLOR_ARGB(255, rand() % 256, rand() % 256, rand() % 256);
            particles[i].life = 2.0f;  // Reset life
        }
    }
}

void Renderparticle()
{
    

  

    for (int i = 0; i < NUM_PARTICLES; ++i)
    {
        if (particles[i].life > 0.0f)
            DrawParticle(particles[i]);
    }

    Update(0.016f);
}

void DrawParticle(const Particle& particle)
{
    Vertex vertex = { particle.position.x, particle.position.y, 0.0f };

    // Set up the world transformation matrix
    D3DXMATRIX matWorld;
    D3DXMatrixScaling(&matWorld, particle.size, particle.size, 1.0f);
    matWorld._41 = vertex.x;
    matWorld._42 = vertex.y;

    // Apply the world transformation matrix
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

    // Draw a point (or use other primitives as needed)
    g_pd3dDevice->SetFVF(D3DFVF_XYZ);
    g_pd3dDevice->DrawPrimitiveUP(D3DPT_POINTLIST, 1, &vertex, sizeof(Vertex));
}


 