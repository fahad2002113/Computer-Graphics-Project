#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>


//----------------For 1st Scene---------------------------------
int currentScene = 1;
float trainOffset1 = -1.2f;  // Left train start position
float trainOffset2 = 1.2f;   // Right train start position
float trainSpeed = 0.007f;   // Movement speed
float carPosX = -1.0f;       // start offscreen
float carSpeed = 0.01f;     // speed of movement
float truckX = -1.5f; // Start off-screen to the left
float truckSpeed = 0.0001f;
const float T_scale = 0.005f; // Adjusted scale for the truck in this environment
const float T_width = 135 * T_scale * 800; // Convert to screen coordinates
float cloudX = -1.2f;   // starting X position
float cloudSpeed = 0.001f; // movement speed
float planeX = -1.2f;   // Starting X position (off screen left)
float planeY = -0.4f;   // Starting Y position (low on screen)
float angle = 30.0f;    // Slight tilt upward
float speed = 0.002f;   // Movement speed

//----------------For 2nd Scene---------------------------------
float cometX = -1.0f;
float cometY = 0.0f;
float cometX1 = -1.0f;
float cometY1 = 0.5f;
float cometSpeed = 0.00005f;
float cometAngle = 60.0f;  // degrees from X-axis
float cometRadius = 0.005f;
float carX11 = -0.0f;     // Initial x position of the car
float carSpeed12 = 0.00006f; // Movement speed
float bridgeLevel = 0.08; // y-position of bridge
float boatX = -0.0f;       // Initial x position of the boat
float boatY = -0.75 - 0.1f; // Slightly below water surface
float boatSpeed = 0.05f;  // Boat movement speed
// Bird positions and movement
float birdX = -1.0f;
float birdY = 0.7f;
float birdSpeed = 0.00001f;
float birdWingFlap = 0.1f;
float birdFlapSpeed = 0.3f;

//----------------For 3rd Scene---------------------------------
float comet3X = -1.0f;
float comet3Y = 1.0f;
float cometSpeed3 = 0.005f;
float cometAngle3 = 340.0f;  // degrees from X-axis
float cometRadius3 = 0.005f;
float boatX3 = 0.4f;       // Initial x position of the boat
float boatY3 = 0.7f; // Slightly below water surface
float boatSpeed3 = 0.05f;  // Boat movement speed


// Convert pixel coordinates to normalized coordinates (-1 to 1)
float toNormX(float x) { return (x / 1920.0f) * 2.0f - 1.0f; }
float toNormY(float y) { return 1.0f - (y / 1080.0f) * 2.0f; }
float toNormW(float w) { return (w / 1920.0f) * 2.0f; }
float toNormH(float h) { return (h / 1080.0f) * 2.0f; }


// Convert int RGB (0–255) to GLfloat[3]
void toGLColorRGB(int r, int g, int b, GLfloat color[3]) {
    color[0] = r / 255.0f;
    color[1] = g / 255.0f;
    color[2] = b / 255.0f;
}


void MetroTrain(float x, float y, float s = 1.0f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);

    //Train dimensions
    const float height = 3.0f;       // total height
    const float slide = 0.45f;  // bottom dark strip
    const float cab_len = 2.5f; // front engine length
    const float body_y = 0.0f;  // bottom
    const float segment = 3.2f;   // window/door segment width
    const int len = 5;
    const float mid_len = len * segment;
    const float L = (cab_len + mid_len)-0.5f; // total train length

    //Main body
    glBegin(GL_QUADS);
        glColor3ub(245, 246, 247);
        glVertex2f(cab_len, body_y);
        glVertex2f(L, body_y);
        glVertex2f(L, body_y + height);
        glVertex2f(cab_len, body_y + height);
    glEnd();

    //slide
    glBegin(GL_QUADS);
        glColor3ub(20, 22, 25);
        glVertex2f(1.7f, body_y);
        glVertex2f(L, body_y);
        glVertex2f(L, body_y + slide);
        glVertex2f(1.7f, body_y + slide);
    glEnd();

    //Front engine
    {
        const float radius = 0.3f;
        const int segments = 10;
        float H_top = body_y + height;

        glBegin(GL_POLYGON); // make the cab a pentagon
        glColor3ub(20, 160, 120);
        glVertex2f(radius+1.4f, (body_y + slide)); // bottom-left
        glVertex2f(cab_len, body_y + slide);     // bottom-right
        glVertex2f(cab_len, H_top);              // top-right
        glVertex2f(radius + 1.8f, H_top);        // top-left slant toward left
        glVertex2f(radius+1.5f, H_top - 0.3f);        // middle-left (slanted edge)
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(170, 175, 180);
        glVertex2f(1.8f, body_y + 1.2f);
        glVertex2f(2.0f, body_y + 1.2f);
        glVertex2f(2.0f, body_y + 2.2f);
        glVertex2f(1.8f, body_y + 2.2f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(170, 175, 180);
        glVertex2f(2.1f, body_y + 1.2f);
        glVertex2f(2.3f, body_y + 1.2f);
        glVertex2f(2.3f, body_y + 2.2f);
        glVertex2f(2.1f, body_y + 2.2f);
        glEnd();

        //Red rectangle below front engine
        glBegin(GL_QUADS);
        glColor3ub(220, 20, 60);
        glVertex2f(1.7f, body_y);          // bottom-left
        glVertex2f(2.3f, body_y);          // bottom-right
        glVertex2f(2.3f, body_y + slide);  // top-right
        glVertex2f(1.7f, body_y + slide);  // top-left
        glEnd();
    }

    // Headlights
    glBegin(GL_QUADS);
        glColor3ub(235, 235, 235);
        glVertex2f(cab_len - 0.5f, body_y + 0.6f);
        glVertex2f(cab_len - 0.7f, body_y + 0.6f);
        glVertex2f(cab_len - 0.7f, body_y + 0.8f);
        glVertex2f(cab_len - 0.5f, body_y + 0.8f);
    glEnd();

    //Headlights
    glBegin(GL_QUADS);
        glColor3ub(235, 235, 235);
        glVertex2f(cab_len - 0.4f, body_y + 0.6f);
        glVertex2f(cab_len - 0.2f, body_y + 0.6f);
        glVertex2f(cab_len - 0.2f, body_y + 0.8f);
        glVertex2f(cab_len - 0.4f, body_y + 0.8f);
    glEnd();

    //Roof green belt
    glBegin(GL_QUADS);
        glColor3ub(20, 160, 120);
        glVertex2f(cab_len - 0.05f, body_y + height - 0.15f);
        glVertex2f(L, body_y + height - 0.15f);
        glVertex2f(L, body_y + height - 0.30f);
        glVertex2f(cab_len - 0.05f, body_y + height - 0.30f);
    glEnd();

    //Doors & windows
    float baseY = body_y + slide;
    float startX = cab_len + 0.35f;

    // Compartment 1
    glBegin(GL_QUADS);
        glColor3ub(170, 175, 180); // window
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206); // door
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 2.50f);
        glVertex2f(startX + 1.85f, baseY + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160); // door inner
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

    // Compartment 2
    startX += segment;
    glBegin(GL_QUADS);
        glColor3ub(170, 175, 180);
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206);
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 2.50f);
        glVertex2f(startX + 1.85f, baseY + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160);
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

    // Compartment 3
    startX += segment;
    glBegin(GL_QUADS);
        glColor3ub(170, 175, 180); // window
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206); // door
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, body_y + 0.10f);
        glVertex2f(startX + 2.45f, body_y + 2.50f);
        glVertex2f(startX + 1.85f, body_y + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160); // door inner
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

    //Comp-4
    startX += segment;
//window
    glBegin(GL_QUADS);
        glColor3ub(170, 175, 180);
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
//Door
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206);
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 2.50f);
        glVertex2f(startX + 1.85f, baseY + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160);
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

//Comp-5
    startX += segment;
//window
    glBegin(GL_QUADS);
        glColor3ub(170, 175, 180);
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
//door
    glBegin(GL_QUADS);
        glColor3ub(20, 160, 120);
        glVertex2f(startX + 2.2f, baseY);
        glVertex2f(startX + 2.4f, baseY);
        glVertex2f(startX + 2.4f, baseY + 2.50f);
        glVertex2f(startX + 2.2f, baseY + 2.50f);
    glEnd();

    glPopMatrix();
}

void sky() {
    // Sky gradient
    glBegin(GL_QUADS);
    glColor3f(0.529f, 0.808f, 0.922f); // Light sky blue (top)
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glColor3f(0.8f, 0.9f, 1.0f); // Lighter blue (bottom)
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void Sun() {
    // Sun
    glColor3ub(255,221,64);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.7f, 0.7f); // Center of circle
    for(int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(0.7f + cos(angle) * 0.1f, 0.7f + sin(angle) * 0.1f);
    }
    glEnd();

    // Sun rays
    glColor3f(1.0f, 0.95f, 0.6f);
    glBegin(GL_LINES);
    for(int i = 0; i < 12; i++) {
        float angle = 2.0f * 3.14159f * i / 12;
        glVertex2f(0.7f + cos(angle) * 0.1f, 0.7f + sin(angle) * 0.1f);
        glVertex2f(0.7f + cos(angle) * 0.15f, 0.7f + sin(angle) * 0.15f);
    }
    glEnd();
}

void Cloud(float x, float y, float size) {
    glColor3f(0.95f, 0.95f, 0.95f);

    // Draw several overlapping circles to form a cloud
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x + cos(angle) * size, y + sin(angle) * size);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + size*0.8f, y);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x + size*0.8f + cos(angle) * size*0.7f, y + sin(angle) * size*0.7f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x - size*0.8f, y);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x - size*0.8f + cos(angle) * size*0.7f, y + sin(angle) * size*0.7f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + size*0.4f, y + size*0.4f);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x + size*0.4f + cos(angle) * size*0.6f, y + size*0.4f + sin(angle) * size*0.6f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x - size*0.4f, y + size*0.4f);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x - size*0.4f + cos(angle) * size*0.6f, y + size*0.4f + sin(angle) * size*0.6f);
    }
    glEnd();
}

void Ground() {
    // Ground
    glColor3ub(72, 80, 85); // Dark gray for road
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.72f);
    glVertex2f(1.0f, -0.72f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    glColor3ub(53, 152, 222);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.13f);
    glVertex2f(1.0f, -0.13f);
    glVertex2f(1.0f, -0.72f);
    glVertex2f(-1.0f, -0.72f);
    glEnd();

    // Road divider
    glColor3ub(167, 163, 145); // green divider
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.74f);
    glVertex2f(1.0f, -0.74f);
    glVertex2f(1.0f, -0.6f);
    glVertex2f(-1.0f, -0.6f);
    glEnd();

    glColor3ub(236, 225, 195); // green divider
    glBegin(GL_LINES);
    glVertex2f(1.0f, -0.6f);
    glVertex2f(-1.0f, -0.6f);
    glEnd();

    glColor3ub(223, 214, 186); // green divider
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.71f);
    glVertex2f(1.0f, -0.71f);
    glVertex2f(1.0f, -0.69f);
    glVertex2f(-1.0f, -0.69f);
    glEnd();

    // Road divider
    glColor3f(0.0f, 1.0f, 0.0f); // green divider
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.13f);
    glVertex2f(1.0f, -0.13f);
    glVertex2f(1.0f, -0.12f);
    glVertex2f(-1.0f, -0.12f);
    glEnd();

    // Road markings
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for(float x = -0.9f; x < 1.0f; x += 0.2f) {
        glVertex2f(x, -0.9f);
        glVertex2f(x + 0.1f, -0.9f);
    }
    glEnd();
}

void MetroOverpass() {
   float lift = 0.4f; // amount to lift the overpass

    // Pillar properties
    int numPillars = 2;
    float leftEdge = -0.8f;
    float rightEdge = 0.8f;
    float pillarX[2] = {leftEdge, rightEdge};

    for (int i = 0; i < numPillars; i++) {
        float x = pillarX[i];
        float baseBottom = -0.72f + lift;  // bottom of pillar
        float baseTop    = -0.37f + lift;   // where pillar touches viaduct
        float pillarWidth = 0.12f;         // base width
        float topWidth    = 0.20f;         // wider top "cap"
        float capHeight   = 0.08f;         // triangular angled section

    // --- Main rectangular body ---
    glBegin(GL_QUADS);
        glColor3ub(157, 154, 139); // left side darker
        glVertex2f(x - pillarWidth/2, baseBottom);
        glVertex2f(x - pillarWidth/2, baseTop);
        glColor3ub(92, 106, 110);   // right side lighter
        glVertex2f(x + pillarWidth/2, baseTop);
        glVertex2f(x + pillarWidth/2, baseBottom);
    glEnd();

    // --- Angled triangular top (cap) ---
    glBegin(GL_TRIANGLES);
        glColor3ub(93, 109, 115);
        glVertex2f(x - pillarWidth/2, baseTop);
        glVertex2f(x + pillarWidth/2, baseTop);
        glVertex2f(x, baseTop + capHeight);
    glEnd();

    // --- Wider top (to match viaduct support shape) ---
    glBegin(GL_QUADS);
        glColor3ub(93, 109, 115);
        glVertex2f(x - topWidth/2, baseTop + capHeight);
        glColor3ub(80, 90, 99);
        glVertex2f(x + topWidth/2, baseTop + capHeight);
        glColor3ub(80, 90, 99);
        glVertex2f(x + pillarWidth/2, baseTop);
        glColor3ub(93, 109, 115);
        glVertex2f(x - pillarWidth/2, baseTop);
    glEnd();

    glBegin(GL_LINES);
        glColor3ub(59, 99, 104);
        glVertex2f(x - pillarWidth/2 -0.015, baseBottom);
        glVertex2f(x + pillarWidth/2 + 0.015, baseBottom);
    glEnd();

    glBegin(GL_QUADS);
        glColor3ub(120, 154, 153);
        glVertex2f(x - pillarWidth/2, baseBottom);
        glVertex2f(x - pillarWidth/2, baseBottom-0.01);
        glVertex2f(x + pillarWidth/2, baseBottom-0.01);
        glVertex2f(x + pillarWidth/2, baseBottom);
    glEnd();
}

    // Platform
    glColor3ub(170, 167, 148);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.15f + lift);
    glVertex2f(-1.0f, -0.15f + lift);
    glEnd();

    // Platform
    glColor3ub(83, 97, 107);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.18f + lift);
    glVertex2f(1.0f, -0.18f + lift);
    glEnd();

    glColor3ub(62, 72, 79);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.24f + lift);
    glVertex2f(1.0f, -0.24f + lift);
    glVertex2f(1.0f, -0.28f + lift);
    glVertex2f(-1.0f, -0.28f + lift);
    glEnd();

    glColor3ub(84, 98, 107);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.28f + lift);
    glVertex2f(-1.0f, -0.28f + lift);
    glEnd();

    // Train 1 (left to right)
    glPushMatrix();
        glTranslatef(trainOffset1, -0.15f + lift, 0.0f); // lift train
        glScalef(0.05f, 0.05f, 1.0f);
        MetroTrain(0.0f, 0.0f);
    glPopMatrix();

    // Train 2 (right to left)
    glPushMatrix();
        glTranslatef(trainOffset2, -0.15f + lift, 0.0f); // lift train
        glScalef(-0.05f, 0.05f, 1.0f);
        MetroTrain(0.0f, 0.0f);
    glPopMatrix();
}

void JetEngineSide(float xOffset, float yOffset, float scale = 1.0f)
{
    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Engine body
    glColor3ub(111, 151, 197);
    glBegin(GL_POLYGON);
      glVertex2f(-0.2f,  0.1f);
      glVertex2f( 0.3f,  0.08f);
      glVertex2f( 0.3f, -0.08f);
      glVertex2f(-0.2f, -0.1f);
    glEnd();

    // cone (front)
    glColor3ub(240, 240, 240);
    glBegin(GL_TRIANGLES);
      glVertex2f(-0.3f,  0.0f);
      glVertex2f(-0.2f,  0.1f);
      glVertex2f(-0.2f, -0.1f);
    glEnd();

    // Exhaust
    glColor3ub(240, 240, 240);
    glBegin(GL_TRIANGLES);
      glVertex2f(0.3f,  0.08f);
      glVertex2f(0.4f, 0.0f);
      glVertex2f(0.3f, -0.08f);
    glEnd();

    // Outline
    glColor3ub(40, 40, 60);
    glBegin(GL_LINE_LOOP);
      glVertex2f(-0.3f,  0.0f);
      glVertex2f(-0.2f,  0.1f);
      glVertex2f(0.3f,  0.08f);
      glVertex2f(0.4f,  0.0f);
      glVertex2f(0.3f, -0.08f);
      glVertex2f(-0.2f, -0.1f);
    glEnd();

    glPopMatrix();
}

void drawSimpleAirplane() {
    // simple body
    glColor3ub(240, 240, 240); // Off-white
    glBegin(GL_POLYGON);
      glVertex2f(0.8f, -0.03f);   // Nose
      glVertex2f(0.6f, 0.08f);
      glVertex2f(-0.8f, 0.08f);
      glVertex2f(-0.9f, 0.08f);
      glVertex2f(-0.6f, -0.05f);
      glVertex2f(0.6f, -0.05f);
    glEnd();

    // Fuselage outline
    glColor3ub(80, 80, 100); // Dark gray-blue
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
      glVertex2f(0.8f, -0.03f);
      glVertex2f(0.6f, 0.08f);
      glVertex2f(-0.8f, 0.08f);
      glVertex2f(-0.9f, 0.08f);
      glVertex2f(-0.6f, -0.05f);
      glVertex2f(0.6f, -0.05f);
    glEnd();

    // Back wing
    glColor3ub(105, 132, 174);
    glBegin(GL_POLYGON);
      glVertex2f(-0.5f, 0.08f);
      glVertex2f(-0.8f, 0.08f);
      glVertex2f(-0.85f, 0.25f);
    glEnd();

    // Tail outline
    glColor3ub(80, 80, 100);
    glBegin(GL_LINE_LOOP);
      glVertex2f(-0.5f, 0.08f);
      glVertex2f(-0.8f, 0.08f);
      glVertex2f(-0.85f, 0.25f);
    glEnd();

    // Underside shade (to give depth)
    glColor3ub(105, 132, 174);
    glBegin(GL_POLYGON);
      glVertex2f(-0.65f,  -0.03f);
      glVertex2f( 0.8f, -0.03f);
      glVertex2f( 0.6f, -0.05f);
      glVertex2f(-0.6f, -0.05f);
    glEnd();

    // Cockpit Window
    glColor3ub(158, 164, 175);
    glBegin(GL_POLYGON);
      glVertex2f(0.55f, 0.06f);
      glVertex2f(0.62f, 0.06f);
      glVertex2f(0.7f, 0.02f);
      glVertex2f(0.55f, 0.02f);
    glEnd();

        // Passenger Windows
    glColor3ub(158, 164, 175);
    float startX = 0.25f;
    for (int i = 0; i < 7; i++) {
        float x = startX - i * 0.1f;
        glBegin(GL_POLYGON);
          glVertex2f(x, 0.055f);
          glVertex2f(x + 0.08f, 0.055f);
          glVertex2f(x + 0.08f, 0.03f);
          glVertex2f(x, 0.03f);
        glEnd();


        glColor3ub(158, 164, 175); // Reset fill color for next
    }
            glColor3ub(158, 164, 175);
        glBegin(GL_LINE_LOOP);
          glVertex2f(0.4, 0.06f);
          glVertex2f(0.4 + 0.08f, 0.06f);
          glVertex2f(0.4 + 0.08f, -0.02f);
          glVertex2f(0.4, -0.02f);
        glEnd();

        glColor3ub(158, 164, 175);
        glBegin(GL_LINE_LOOP);
          glVertex2f(-0.5, 0.06f);
          glVertex2f(-0.5 + 0.08f, 0.06f);
          glVertex2f(-0.5 + 0.08f, -0.02f);
          glVertex2f(-0.5, -0.02f);
        glEnd();

        glColor3ub(105, 132, 174);
        glBegin(GL_POLYGON);
          glVertex2f(-0.3, 0.00f);
          glVertex2f(-0.3 + 0.35f, 0.00f);
          glVertex2f(-0.3 + 0.35f, -0.02f);
          glVertex2f(-0.3, -0.02f);
        glEnd();

        glColor3ub(105, 132, 174);
        glBegin(GL_POLYGON);
          glVertex2f(-0.7, 0.06f);
          glVertex2f(-0.7 + 0.15f, 0.06f);
          glVertex2f(-0.7 + 0.15f, 0.04f);
          glVertex2f(-0.7, 0.04f);
        glEnd();

JetEngineSide(0.15f, -0.04f, 0.3f);

}

// filled circle
void drawFilledCircle(float cx, float cy, float r, int segments = 40) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

// half ellipse / arc
void drawEllipseArc(float cx, float cy, float rx, float ry,
                    float startAngle, float endAngle, int segments = 50) {
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; i++) {
        float theta = startAngle + (endAngle - startAngle) * ((float)i / (float)segments);
        glVertex2f(cx + rx * cosf(theta), cy + ry * sinf(theta));
    }
    glEnd();
}

// (used for wheels)
void circle(float rx, float ry, float cx, float cy) {
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416f / 180.0f;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

// car
void draw2DCar() {
    glPushMatrix();
    glTranslatef(carPosX, -0.8f, 0.0f); // move car by carPosX
    glScalef(0.19f, 0.25f, 1.0f); // scale car to half size

    // Car body
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
      glVertex2f(-0.9f, 0.0f);
      glVertex2f(-0.7f, 0.4f);
      glVertex2f(0.3f, 0.4f);
      glVertex2f(0.3f, 0.0f);
    glEnd();

    // Bonnet
    glColor3f(0.0f, 0.0f, 1.0f);
    drawEllipseArc(0.3f, 0.0f, 0.7f, 0.4f, 0.0f, M_PI/2, 30);
    drawEllipseArc(-0.7f, 0.0f, 0.23f, 0.4f, M_PI/2, M_PI, 30);

    // Roof
    glBegin(GL_POLYGON);
      glVertex2f(-0.7f, 0.4f);
      glVertex2f(-0.83f, 0.3f);
      glVertex2f(-0.7f, 0.6f);
      glVertex2f(0.18f, 0.6f);
      glVertex2f(0.56f, 0.38f);
    glEnd();

    // Left window
    glColor3f(0.15f, 0.15f, 0.2f);
    glBegin(GL_QUADS);
      glVertex2f(-0.7f, 0.38f);
      glVertex2f(-0.15f, 0.38f);
      glVertex2f(-0.15f, 0.57f);
      glVertex2f(-0.65f, 0.57f);
    glEnd();

    // Right window
    glBegin(GL_QUADS);
      glVertex2f(-0.1f, 0.38f);
      glVertex2f(0.45f, 0.38f);
      glVertex2f(0.15f, 0.57f);
      glVertex2f(-0.1f, 0.57f);
    glEnd();

    // Lights
    glColor3f(1.0f, 1.0f, 0.6f); // headlight
    drawFilledCircle(0.9f, 0.1f, 0.03f, 24);
    glColor3f(1.0f, 0.2f, 0.2f); // taillight
    drawFilledCircle(-0.84f, 0.3f, 0.03f, 24);

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, 0.03f);
    glVertex2f(0.4f, 0.03f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.9f, 0.03f);
    glVertex2f(-0.72f, 0.03f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.12f, 0.36f);
    glVertex2f(-0.12f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.75f, 0.36f);
    glVertex2f(0.52f, 0.36f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.0f, 0.28f);
    glVertex2f(0.1f, 0.28f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.6f, 0.28f);
    glVertex2f(-0.5f, 0.28f);
    glEnd();

    // Wheels
    float wheelRadius = 0.18f;
    float rearWheelX = -0.7f;
    float frontWheelX = 0.58f;
    float wheelYOffset = -0.03f;
    glColor3f(0.07f, 0.07f, 0.07f);
    drawFilledCircle(rearWheelX, wheelYOffset, wheelRadius, 40);
    drawFilledCircle(frontWheelX, wheelYOffset, wheelRadius, 40);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawFilledCircle(rearWheelX, wheelYOffset, wheelRadius * 0.55f, 30);
    drawFilledCircle(frontWheelX, wheelYOffset, wheelRadius * 0.55f, 30);

    glPopMatrix();
}

// Truck
void drawTruck() {
    glPushMatrix();

    // truck on the road
    glTranslatef(truckX-1.8, -1.15f, 0.0f);
    glScalef(T_scale, T_scale, 1.0f);

    // --- Truck body ---
    glColor3ub(255, 165, 90);
    glBegin(GL_POLYGON);
    glVertex2d(400, 40);
    glVertex2d(505, 40);
    glVertex2d(505, 110);
    glVertex2d(400, 110);
    glEnd();

    glColor3ub(255, 250, 240); // off-white
    glBegin(GL_POLYGON);
    glVertex2d(405, 55);
    glVertex2d(500, 55);
    glVertex2d(500, 100);
    glVertex2d(405, 100);
    glEnd();

    // Front bumper
    glColor3ub(220, 20, 60);
    glBegin(GL_POLYGON);
    glVertex2d(505, 40);
    glVertex2d(535, 40);
    glVertex2d(535, 70);
    glVertex2d(505, 70);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(505, 70);
    glVertex2d(535, 70);
    glVertex2d(525, 90);
    glVertex2d(505, 90);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(510, 64);
    glVertex2d(515, 64);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 60);
    glVertex2d(535, 60);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 45);
    glVertex2d(535, 45);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 50);
    glVertex2d(535, 50);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 55);
    glVertex2d(535, 55);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(506, 69);
    glVertex2d(531, 69);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(506, 69);
    glVertex2d(506, 86);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(506, 86);
    glVertex2d(525, 86);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 86);
    glVertex2d(531, 69);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(506, 50);
    glVertex2d(506, 69);
    glEnd();

    glColor3ub(192, 192, 192);
    glBegin(GL_POLYGON);
    glVertex2d(525, 45);
    glVertex2d(535, 45);
    glVertex2d(535, 50);
    glVertex2d(525, 50);
    glEnd();

    glColor3ub(192, 192, 192);
    glBegin(GL_POLYGON);
    glVertex2d(525, 55);
    glVertex2d(535, 55);
    glVertex2d(535, 60);
    glVertex2d(525, 60);
    glEnd();

    // Truck window
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(507, 70);
    glVertex2d(530, 70);
    glVertex2d(525, 85);
    glVertex2d(507, 85);
    glEnd();

    // Wheels
    glColor3ub(0, 0, 0);
    circle(10, 14, 420, 40);
    circle(10, 14, 510, 40);

    glColor3f(0.7f, 0.7f, 0.7f);
    circle(6, 10, 420, 40);
    circle(6, 10, 510, 40);

    glColor3f(1.0f, 1.0f, 0.6f);
    circle(1.5, 1.5, 534, 47.5);

    glPopMatrix();

    // Move truck
    truckX += truckSpeed;
    if (truckX > 1.5f) {
        truckX = -1.5f - (T_width / 800.0f);
    }
}

void drawBuilding(float x, float width, float height, int windowsX, int windowsY,
                  GLubyte r, GLubyte g, GLubyte b, float scale = 1.0f, float lineY = -0.12f) {
    // Calculate scaled height
    float scaledHeight = height * scale;

    // Apply translation so bottom aligns with lineY
    glPushMatrix();
    glTranslatef(x, lineY, 0.0f); // move bottom to lineY
    glScalef(scale, scale, 0.5f); // scale width & height

    // Building structure
    glColor3ub(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(width, 0.0f);
        glVertex2f(width, height);
        glVertex2f(0.0f, height);
    glEnd();

    // Windows
    float windowWidth = width * 0.5f / windowsX;
    float windowHeight = height * 0.5f / windowsY;
    float spacingX = width * 0.1f / (windowsX + 1);
    float spacingY = height * 0.1f / (windowsY + 1);

    for(int i = 0; i < windowsX; i++) {
        for(int j = 0; j < windowsY; j++) {
            glColor3ub(180, 200, 220); // lighter windows
            float windowX = spacingX * (i+1) + windowWidth * i;
            float windowY = spacingY * (j+1) + windowHeight * j;

            glBegin(GL_QUADS);
                glVertex2f(windowX, windowY);
                glVertex2f(windowX + windowWidth, windowY);
                glVertex2f(windowX + windowWidth, windowY + windowHeight);
                glVertex2f(windowX, windowY + windowHeight);
            glEnd();
        }
    }

    glPopMatrix();
}

void urbanArea() {
    float lineY = -0.12f; // baseline for buildings

    struct Building {
        float x, width, height;
        int windowsX, windowsY;
        GLubyte r, g, b;
        float scale;
    };

    Building buildings[] = {
        {-1.0f, 0.12f, 0.3f, 2, 3, 200, 200, 220, 0.5f},
        {-0.95f, 0.1f, 0.22f, 1, 2, 180, 200, 190, 0.5f},
        {-0.9f, 0.13f, 0.25f, 2, 3, 210, 200, 180, 0.5f},
        {-0.8f, 0.11f, 0.32f, 3, 4, 190, 210, 200, 0.5f},
        {-0.75f, 0.12f, 0.3f, 2, 3, 200, 190, 210, 0.5f},
        {-0.7f, 0.1f, 0.26f, 2, 3, 210, 200, 180, 0.5f},
        {-0.65f, 0.12f, 0.28f, 2, 4, 180, 200, 200, 0.5f},
        {-0.55f, 0.11f, 0.3f, 3, 4, 220, 210, 200, 0.5f},
        {-0.5f, 0.1f, 0.27f, 2, 3, 190, 200, 180, 0.5f},
        {-0.45f, 0.12f, 0.32f, 3, 5, 200, 190, 210, 0.5f},
        {-0.4f, 0.1f, 0.25f, 2, 3, 210, 200, 180, 0.5f},
        {-0.35f, 0.13f, 0.3f, 2, 4, 180, 200, 200, 0.5f},
        {-0.3f, 0.12f, 0.28f, 2, 3, 200, 180, 210, 0.5f},
        {-0.2f, 0.1f, 0.26f, 2, 3, 200, 190, 180, 0.5f},
        {-0.15f, 0.12f, 0.3f, 2, 4, 210, 200, 190, 0.5f},
        {-0.1f, 0.1f, 0.25f, 2, 3, 180, 200, 210, 0.5f},
        {-0.05f, 0.13f, 0.32f, 3, 5, 200, 180, 200, 0.5f},
        {0.0f, 0.1f, 0.28f, 2, 3, 210, 200, 180, 0.5f},
        {0.05f, 0.11f, 0.3f, 2, 4, 190, 210, 200, 0.5f},
        {0.1f, 0.12f, 0.26f, 2, 3, 200, 190, 210, 0.5f},
        {0.15f, 0.1f, 0.32f, 3, 4, 210, 200, 180, 0.5f},
        {0.2f, 0.12f, 0.3f, 2, 3, 180, 200, 200, 0.5f},
        {0.25f, 0.11f, 0.28f, 2, 4, 200, 180, 210, 0.5f},
        {0.3f, 0.1f, 0.25f, 2, 3, 190, 210, 200, 0.5f},
        {0.35f, 0.13f, 0.32f, 3, 5, 210, 200, 180, 0.5f},
        {0.4f, 0.12f, 0.3f, 2, 3, 200, 190, 210, 0.5f},
        {0.5f, 0.1f, 0.28f, 2, 3, 200, 180, 190, 0.5f},
        {0.55f, 0.12f, 0.3f, 2, 4, 210, 200, 180, 0.5f},
        {0.6f, 0.1f, 0.25f, 2, 3, 190, 210, 200, 0.5f},
        {0.65f, 0.13f, 0.32f, 3, 4, 200, 180, 210, 0.5f},
        {0.7f, 0.12f, 0.28f, 2, 3, 210, 200, 180, 0.5f},
        {0.75f, 0.1f, 0.3f, 2, 4, 180, 200, 200, 0.5f},
        {0.85f, 0.12f, 0.32f, 3, 5, 210, 200, 180, 0.5f},
        {0.9f, 0.1f, 0.28f, 2, 3, 190, 210, 200, 0.5f},
        {0.95f, 0.12f, 0.3f, 2, 4, 200, 180, 190, 0.5f}
    };

    int n = sizeof(buildings) / sizeof(buildings[0]);
    for(int i = 0; i < n; i++) {
        drawBuilding(buildings[i].x, buildings[i].width, buildings[i].height,
                     buildings[i].windowsX, buildings[i].windowsY,
                     buildings[i].r, buildings[i].g, buildings[i].b,
                     buildings[i].scale, lineY);
    glColor3ub(150, 150, 150);
            glBegin(GL_LINES);
            glVertex2f(buildings[5].x + buildings[5].width/2 + (-0.005), lineY + buildings[5].height*buildings[5].scale);
            glVertex2f(buildings[5].x + buildings[5].width/2 + (-0.005), lineY + buildings[5].height*buildings[5].scale + 0.05f);
            glEnd();
    }
}


void MetroTrain4(float x, float y, float s = 1.0f)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(s, s, 1.0f);

    // Train dimensions
    const float height = 3.0f;       // total height
    const float slide = 0.45f;  // bottom dark strip
    const float cab_len = 2.5f; // front engine length
    const float body_y = 0.0f;  // bottom
    const float segment = 3.2f;   // window/door segment width
    const int len = 5;
    const float mid_len = len * segment;
    const float L = (cab_len + mid_len)-0.5f; // total train length

    // Main body
    glBegin(GL_QUADS);
        glColor3ub(180, 185, 190); // Darker for night
        glVertex2f(cab_len, body_y);
        glVertex2f(L, body_y);
        glVertex2f(L, body_y + height);
        glVertex2f(cab_len, body_y + height);
    glEnd();

    //slide
    glBegin(GL_QUADS);
        glColor3ub(15, 17, 20); // Darker slide
        glVertex2f(1.7f, body_y);
        glVertex2f(L, body_y);
        glVertex2f(L, body_y + slide);
        glVertex2f(1.7f, body_y + slide);
    glEnd();

    //Front engine/cab
    {
        const float radius = 0.3f;
        const int segments = 10;
        float H_top = body_y + height;

        glBegin(GL_POLYGON); // make the cab a pentagon - darker for night
        glColor3ub(15, 120, 90); // Darker green for night
        glVertex2f(radius+1.4f, (body_y + slide));       // bottom-left
        glVertex2f(cab_len, body_y + slide);     // bottom-right
        glVertex2f(cab_len, H_top);              // top-right
        glVertex2f(radius + 1.8f, H_top);        // top-left slant toward left
        glVertex2f(radius+1.5f, H_top - 0.3f);        // middle-left (slanted edge)
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(255, 255, 200); // light blue window
        glVertex2f(1.8f, body_y + 1.2f);
        glVertex2f(2.0f, body_y + 1.2f);
        glVertex2f(2.0f, body_y + 2.2f);
        glVertex2f(1.8f, body_y + 2.2f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3ub(255, 255, 200); // light blue window
        glVertex2f(2.1f, body_y + 1.2f);
        glVertex2f(2.3f, body_y + 1.2f);
        glVertex2f(2.3f, body_y + 2.2f);
        glVertex2f(2.1f, body_y + 2.2f);
        glEnd();

        // Red rectangle below front engine
        glBegin(GL_QUADS);
        glColor3ub(220, 20, 60); // red color
        glVertex2f(1.7f, body_y);          // bottom-left
        glVertex2f(2.3f, body_y);          // bottom-right
        glVertex2f(2.3f, body_y + slide);  // top-right
        glVertex2f(1.7f, body_y + slide);  // top-left
        glEnd();
    }

    // Headlights
    glBegin(GL_QUADS);
        glColor3ub(235, 235, 235);
        glVertex2f(cab_len - 0.5f, body_y + 0.6f);
        glVertex2f(cab_len - 0.7f, body_y + 0.6f);
        glVertex2f(cab_len - 0.7f, body_y + 0.8f);
        glVertex2f(cab_len - 0.5f, body_y + 0.8f);
    glEnd();

    // Headlights
    glBegin(GL_QUADS);
        glColor3ub(235, 235, 235);
        glVertex2f(cab_len - 0.4f, body_y + 0.6f);
        glVertex2f(cab_len - 0.2f, body_y + 0.6f);
        glVertex2f(cab_len - 0.2f, body_y + 0.8f);
        glVertex2f(cab_len - 0.4f, body_y + 0.8f);
    glEnd();


    //Roof green belt
    glBegin(GL_QUADS);
        glColor3ub(15, 120, 90); // Darker green for night
        glVertex2f(cab_len - 0.05f, body_y + height - 0.15f);
        glVertex2f(L, body_y + height - 0.15f);
        glVertex2f(L, body_y + height - 0.30f);
        glVertex2f(cab_len - 0.05f, body_y + height - 0.30f);
    glEnd();

    //Doors & windows
    float baseY = body_y + slide;
    float startX = cab_len + 0.35f;

    // Compartment 1
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 200); // window
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206); // door
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 2.50f);
        glVertex2f(startX + 1.85f, baseY + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160); // door inner
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

    // Compartment 2
    startX += segment;
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 200);
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206);
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 2.50f);
        glVertex2f(startX + 1.85f, baseY + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160);
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

    // Compartment 3
    startX += segment;
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 200); // window
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206); // door
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 2.50f);
        glVertex2f(startX + 1.85f, baseY + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160); // door inner
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

    // Compartment 4
    startX += segment;
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 200); // window
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(200, 203, 206); // door
        glVertex2f(startX + 1.85f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 0.10f);
        glVertex2f(startX + 2.45f, baseY + 2.50f);
        glVertex2f(startX + 1.85f, baseY + 2.50f);
    glEnd();
    glBegin(GL_QUADS);
        glColor3ub(150, 155, 160); // door inner
        glVertex2f(startX + 1.98f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 1.30f);
        glVertex2f(startX + 2.32f, baseY + 2.20f);
        glVertex2f(startX + 1.98f, baseY + 2.20f);
    glEnd();

    // Compartment 5
    startX += segment;
    glBegin(GL_QUADS);
        glColor3ub(255, 255, 200); // window
        glVertex2f(startX + 0.10f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 1.25f);
        glVertex2f(startX + 1.55f, baseY + 2.10f);
        glVertex2f(startX + 0.10f, baseY + 2.10f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3ub(20, 160, 120); // door
        glVertex2f(startX + 2.2f, baseY);
        glVertex2f(startX + 2.4f, baseY);
        glVertex2f(startX + 2.4f, baseY + 2.50f);
        glVertex2f(startX + 2.2f, baseY + 2.50f);
    glEnd();

    glPopMatrix();
}

void sky4() {
    // Night sky gradient
    glBegin(GL_QUADS);
    glColor3f(0.05f, 0.05f, 0.15f); // Dark blue-black (top)
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glColor3f(0.1f, 0.1f, 0.2f); // Slightly lighter dark blue (bottom)
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void drawMoon4() {
    // Moon
    glColor3ub(240, 240, 250); // Silver-white moon
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.7f, 0.7f); // Center of circle
    for(int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(0.7f + cos(angle) * 0.1f, 0.7f + sin(angle) * 0.1f);
    }
    glEnd();

    // Moon craters
    glColor3ub(200, 200, 210);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.65f, 0.72f); // Small crater
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(0.65f + cos(angle) * 0.02f, 0.72f + sin(angle) * 0.02f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.72f, 0.68f); // Another small crater
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(0.72f + cos(angle) * 0.015f, 0.68f + sin(angle) * 0.015f);
    }
    glEnd();
}

void drawStars4() {
    glColor3f(1.0f, 1.0f, 1.0f); // White stars

    // Draw multiple stars across the sky
    float starPositions[][2] = {
        {-0.8f, 0.9f}, {-0.6f, 0.85f}, {-0.4f, 0.95f}, {-0.2f, 0.88f}, {0.0f, 0.92f},
        {0.2f, 0.87f}, {0.4f, 0.94f}, {0.6f, 0.89f}, {0.8f, 0.91f}, {0.9f, 0.86f},
        {-0.9f, 0.7f}, {-0.7f, 0.75f}, {-0.5f, 0.72f}, {-0.3f, 0.78f}, {-0.1f, 0.74f},
        {0.1f, 0.76f}, {0.3f, 0.73f}, {0.5f, 0.79f}, {0.7f, 0.77f}, {0.85f, 0.71f},
        {-0.85f, 0.5f}, {-0.65f, 0.55f}, {-0.45f, 0.52f}, {-0.25f, 0.58f}, {-0.05f, 0.54f},
        {0.05f, 0.56f}, {0.25f, 0.53f}, {0.45f, 0.59f}, {0.65f, 0.57f}, {0.8f, 0.51f}
    };

    for(int i = 0; i < 30; i++) {
        glBegin(GL_POINTS);
        glVertex2f(starPositions[i][0], starPositions[i][1]);
        glEnd();
    }

    // Draw some brighter stars
    glPointSize(2.0f);
    glColor3f(0.9f, 0.9f, 1.0f); // Slightly blue-white
    for(int i = 0; i < 5; i++) {
        glBegin(GL_POINTS);
        glVertex2f(starPositions[i*6][0], starPositions[i*6][1]);
        glEnd();
    }
    glPointSize(1.0f); // Reset point size
}

void Cloud4(float x, float y, float size) {
    glColor3f(0.3f, 0.3f, 0.4f); // Dark clouds for night

    // overlapping circles to form a cloud
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x + cos(angle) * size, y + sin(angle) * size);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + size*0.8f, y);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x + size*0.8f + cos(angle) * size*0.7f, y + sin(angle) * size*0.7f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x - size*0.8f, y);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x - size*0.8f + cos(angle) * size*0.7f, y + sin(angle) * size*0.7f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + size*0.4f, y + size*0.4f);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x + size*0.4f + cos(angle) * size*0.6f, y + size*0.4f + sin(angle) * size*0.6f);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x - size*0.4f, y + size*0.4f);
    for(int i = 0; i <= 20; i++) {
        float angle = 2.0f * 3.14159f * i / 20;
        glVertex2f(x - size*0.4f + cos(angle) * size*0.6f, y + size*0.4f + sin(angle) * size*0.6f);
    }
    glEnd();
}

void Ground4() {
    // Ground - darker for night
    glColor3ub(40, 45, 50); // Much darker gray for road
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.72f);
    glVertex2f(1.0f, -0.72f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Road - darker blue for night
    glColor3ub(30, 40, 60); // Dark blue-gray for road
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.13f);
    glVertex2f(1.0f, -0.13f);
    glVertex2f(1.0f, -0.72f);
    glVertex2f(-1.0f, -0.72f);
    glEnd();

    // Road divider - darker for night
    glColor3ub(80, 85, 90); // Dark gray divider
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.74f);
    glVertex2f(1.0f, -0.74f);
    glVertex2f(1.0f, -0.6f);
    glVertex2f(-1.0f, -0.6f);
    glEnd();

    glColor3ub(120, 125, 130); // Lighter gray line
    glBegin(GL_LINES);
    glVertex2f(1.0f, -0.6f);
    glVertex2f(-1.0f, -0.6f);
    glEnd();

    glColor3ub(100, 105, 110); // Dark gray divider
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.71f);
    glVertex2f(1.0f, -0.71f);
    glVertex2f(1.0f, -0.69f);
    glVertex2f(-1.0f, -0.69f);
    glEnd();


    // Road divider - darker for night
    glColor3ub(60, 70, 80); // Dark blue-gray divider
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.13f);
    glVertex2f(1.0f, -0.13f);
    glVertex2f(1.0f, -0.12f);
    glVertex2f(-1.0f, -0.12f);
    glEnd();

    // Road markings - dimmer for night
    glColor3f(0.7f, 0.7f, 0.7f); // Dim white
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    for(float x = -0.9f; x < 1.0f; x += 0.2f) {
        glVertex2f(x, -0.9f);
        glVertex2f(x + 0.1f, -0.9f);
    }
    glEnd();
}

void draw2DCar4() {
    glPushMatrix();
    glTranslatef(carPosX, -0.8f, 0.0f); // move car by carPosX
    glScalef(0.19f, 0.25f, 1.0f);

    // Car body
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
      glVertex2f(-0.9f, 0.0f);
      glVertex2f(-0.7f, 0.4f);
      glVertex2f(0.3f, 0.4f);
      glVertex2f(0.3f, 0.0f);
    glEnd();

    // Bonnet
    glColor3f(0.0f, 0.0f, 1.0f);
    drawEllipseArc(0.3f, 0.0f, 0.7f, 0.4f, 0.0f, M_PI/2, 30);
    drawEllipseArc(-0.7f, 0.0f, 0.23f, 0.4f, M_PI/2, M_PI, 30);

    // Roof
    glBegin(GL_POLYGON);
      glVertex2f(-0.7f, 0.4f);
      glVertex2f(-0.83f, 0.3f);
      glVertex2f(-0.7f, 0.6f);
      glVertex2f(0.18f, 0.6f);
      glVertex2f(0.56f, 0.38f);
    glEnd();

    // Left window
    glColor3ub(250, 250, 200);
    glBegin(GL_QUADS);
      glVertex2f(-0.7f, 0.38f);
      glVertex2f(-0.15f, 0.38f);
      glVertex2f(-0.15f, 0.57f);
      glVertex2f(-0.65f, 0.57f);
    glEnd();

    // Right window
    glColor3ub(250, 250, 200);
    glBegin(GL_QUADS);
      glVertex2f(-0.1f, 0.38f);
      glVertex2f(0.45f, 0.38f);
      glVertex2f(0.15f, 0.57f);
      glVertex2f(-0.1f, 0.57f);
    glEnd();

    // Lights - realistic for night
    glColor3f(1.0f, 1.0f, 0.6f); // Brighter yellow headlight
    drawFilledCircle(0.9f, 0.1f, 0.03f, 24);
    glColor3f(0.8f, 0.2f, 0.2f); // taillight
    drawFilledCircle(-0.84f, 0.3f, 0.03f, 24);

    // Long spread headlight beam with gradual fade effect
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f(0.9f, 0.9f, 0.6f, 0.8f); // Bright at source
    glVertex2f(0.9f, 0.1f);            // Headlight position

    glColor4f(0.9f, 0.9f, 0.6f, 0.4f); // Faded at edges
    glVertex2f(0.9f, 0.05f);
    glVertex2f(0.9f, 0.15f);

    glColor4f(0.9f, 0.9f, 0.6f, 0.2f); // Very faded at far end
    glVertex2f(1.8f, 0.3f);
    glVertex2f(1.8f, -0.2f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, 0.03f);
    glVertex2f(0.4f, 0.03f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.9f, 0.03f);
    glVertex2f(-0.72f, 0.03f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.12f, 0.36f);
    glVertex2f(-0.12f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.75f, 0.36f);
    glVertex2f(0.52f, 0.36f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.0f, 0.28f);
    glVertex2f(0.1f, 0.28f);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.6f, 0.28f);
    glVertex2f(-0.5f, 0.28f);
    glEnd();

    // Wheels
    float wheelRadius = 0.18f;
    float rearWheelX = -0.7f;
    float frontWheelX = 0.58f;
    float wheelYOffset = -0.03f;
    glColor3f(0.07f, 0.07f, 0.07f);
    drawFilledCircle(rearWheelX, wheelYOffset, wheelRadius, 40);
    drawFilledCircle(frontWheelX, wheelYOffset, wheelRadius, 40);

    glColor3f(0.7f, 0.7f, 0.7f);
    drawFilledCircle(rearWheelX, wheelYOffset, wheelRadius * 0.55f, 30);
    drawFilledCircle(frontWheelX, wheelYOffset, wheelRadius * 0.55f, 30);

    glPopMatrix();
}

void drawTruck4() {
    glPushMatrix();

    // Position the truck on the road
    glTranslatef(truckX-1.8, -1.15f, 0.0f);
    glScalef(T_scale, T_scale, 1.0f);

    // --- Truck body ---
    glColor3ub(255, 165, 90);
    glBegin(GL_POLYGON);
    glVertex2d(400, 40);
    glVertex2d(505, 40);
    glVertex2d(505, 110);
    glVertex2d(400, 110);
    glEnd();

    glColor3ub(255, 250, 240); // off-white
    glBegin(GL_POLYGON);
    glVertex2d(405, 55);
    glVertex2d(500, 55);
    glVertex2d(500, 100);
    glVertex2d(405, 100);
    glEnd();

    // --- Front bumper ---
    glColor3ub(220, 20, 60);
    glBegin(GL_POLYGON);
    glVertex2d(505, 40);
    glVertex2d(535, 40);
    glVertex2d(535, 70);
    glVertex2d(505, 70);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(505, 70);
    glVertex2d(535, 70);
    glVertex2d(525, 90);
    glVertex2d(505, 90);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(510, 64);
    glVertex2d(515, 64);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 60);
    glVertex2d(535, 60);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 45);
    glVertex2d(535, 45);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 50);
    glVertex2d(535, 50);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 55);
    glVertex2d(535, 55);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(506, 69);
    glVertex2d(531, 69);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(506, 69);
    glVertex2d(506, 86);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(506, 86);
    glVertex2d(525, 86);
    glEnd();

    glBegin(GL_LINES);
    glVertex2d(525, 86);
    glVertex2d(531, 69);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2d(506, 50);
    glVertex2d(506, 69);
    glEnd();

    glColor3ub(192, 192, 192);
    glBegin(GL_POLYGON);
    glVertex2d(525, 45);
    glVertex2d(535, 45);
    glVertex2d(535, 50);
    glVertex2d(525, 50);
    glEnd();

    glColor3ub(192, 192, 192);
    glBegin(GL_POLYGON);
    glVertex2d(525, 55);
    glVertex2d(535, 55);
    glVertex2d(535, 60);
    glVertex2d(525, 60);
    glEnd();

    // --- Truck window ---
    glColor3ub(220, 220, 220);
    glBegin(GL_POLYGON);
    glVertex2d(507, 70);
    glVertex2d(530, 70);
    glVertex2d(525, 85);
    glVertex2d(507, 85);
    glEnd();

    // --- Wheels ---
    glColor3ub(0, 0, 0);
    circle(10, 14, 420, 40);
    circle(10, 14, 510, 40);

    glColor3f(0.7f, 0.7f, 0.7f);
    circle(6, 10, 420, 40);
    circle(6, 10, 510, 40);
    // Truck headlight - off
    glColor3f(1.0f, 1.0f, 0.6f); // Dark headlight (off)
    drawFilledCircle(534, 47.5, 3.0f, 24);
    glColor3f(0.8f, 0.2f, 0.2f); // Dark taillight (off)
    drawFilledCircle(400, 47.5, 3.0f, 24);

    // Long spread headlight beam pointing left to right
glBegin(GL_TRIANGLE_STRIP);
glColor4f(0.9f, 0.9f, 0.6f, 0.8f); // Bright at source
glVertex2f(534, 47.5);

glColor4f(0.9f, 0.9f, 0.6f, 0.4f); // Faded at edges
glVertex2f(534, 45.125);           // (converted from 1.67f, 0.95f)
glVertex2f(534, 49.875);           // (converted from 1.67f, 1.05f)

glColor4f(0.9f, 0.9f, 0.6f, 0.2f); // Very faded at far end
glVertex2f(580, 42.75);
glVertex2f(580, 17.125);
glEnd();

    glPopMatrix();

    // Move truck
    truckX += truckSpeed;
    if (truckX > 1.5f) {
        truckX = -1.5f - (T_width / 800.0f);
    }
}

void MetroOverpass4() {
   float lift = 0.4f; // amount to lift the overpass

// Pillar properties
int numPillars = 2;
float leftEdge = -0.8f;
float rightEdge = 0.8f;
float pillarX[2] = {leftEdge, rightEdge};

for (int i = 0; i < numPillars; i++) {
    float x = pillarX[i];
    float baseBottom = -0.72f + lift;  // bottom of pillar
    float baseTop    = -0.37f + lift;   // where pillar touches viaduct
    float pillarWidth = 0.12f;         // base width
    float topWidth    = 0.20f;         // wider top "cap"
    float capHeight   = 0.08f;         // triangular angled section

    // --- Main rectangular body ---
    glBegin(GL_QUADS);
        glColor3ub(157, 154, 139); // left side darker
        glVertex2f(x - pillarWidth/2, baseBottom);
        glVertex2f(x - pillarWidth/2, baseTop);
        glColor3ub(92, 106, 110);   // right side lighter
        glVertex2f(x + pillarWidth/2, baseTop);
        glVertex2f(x + pillarWidth/2, baseBottom);
    glEnd();

    // --- Angled triangular top (cap) ---
    glBegin(GL_TRIANGLES);
        glColor3ub(93, 109, 115);
        glVertex2f(x - pillarWidth/2, baseTop);
        glVertex2f(x + pillarWidth/2, baseTop);
        glVertex2f(x, baseTop + capHeight);
    glEnd();

    // --- Wider top
    glBegin(GL_QUADS);
        glColor3ub(93, 109, 115);
        glVertex2f(x - topWidth/2, baseTop + capHeight);
        glColor3ub(80, 90, 99);
        glVertex2f(x + topWidth/2, baseTop + capHeight);
        glColor3ub(80, 90, 99);
        glVertex2f(x + pillarWidth/2, baseTop);
        glColor3ub(93, 109, 115);
        glVertex2f(x - pillarWidth/2, baseTop);
    glEnd();

    glBegin(GL_LINES);
        glColor3ub(59, 99, 104);
        glVertex2f(x - pillarWidth/2 -0.015, baseBottom);
        glVertex2f(x + pillarWidth/2 + 0.015, baseBottom);
    glEnd();

    glBegin(GL_QUADS);
        glColor3ub(120, 154, 153);
        glVertex2f(x - pillarWidth/2, baseBottom);
        glVertex2f(x - pillarWidth/2, baseBottom-0.01);

        glVertex2f(x + pillarWidth/2, baseBottom-0.01);
        glVertex2f(x + pillarWidth/2, baseBottom);

    glEnd();
}
    // Platform - darker for night
    glColor3ub(100, 105, 110);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.15f + lift);
    glVertex2f(-1.0f, -0.15f + lift);
    glEnd();
    // Platform lines - darker for night
    glColor3ub(60, 70, 80);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.18f + lift);
    glVertex2f(1.0f, -0.18f + lift);
    glEnd();

    glColor3ub(50, 60, 70);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.24f + lift);
    glVertex2f(1.0f, -0.24f + lift);
    glVertex2f(1.0f, -0.28f + lift);
    glVertex2f(-1.0f, -0.28f + lift);
    glEnd();

    glColor3ub(70, 80, 90);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.3f + lift);
    glVertex2f(1.0f, -0.28f + lift);
    glVertex2f(-1.0f, -0.28f + lift);
    glEnd();

    // Train 1 (left to right)
    glPushMatrix();
        glTranslatef(trainOffset1, -0.15f + lift, 0.0f); // lift train
        glScalef(0.05f, 0.05f, 1.0f);
        MetroTrain4(0.0f, 0.0f);
    glPopMatrix();

    // Train 2 (right to left)
    glPushMatrix();
        glTranslatef(trainOffset2, -0.15f + lift, 0.0f); // lift train
        glScalef(-0.05f, 0.05f, 1.0f);
        MetroTrain4(0.0f, 0.0f);
    glPopMatrix();
}

void drawStreetLights4() {
    float lightPositions[] = {-0.4f, 0.4f};

    for(int i = 0; i < 2; i++) {
        float x = lightPositions[i];

        // Main pole (taller and thicker) - steel color
        glColor3ub(180, 180, 185); // Light steel/silver
        glBegin(GL_QUADS);
        glVertex2f(x - 0.015f, -0.72f);
        glVertex2f(x + 0.015f, -0.72f);
        glVertex2f(x + 0.015f, -0.2f);
        glVertex2f(x - 0.015f, -0.2f);
        glEnd();

        // Pole base - darker steel
        glColor3ub(160, 160, 165); // Darker steel
        glBegin(GL_QUADS);
        glVertex2f(x - 0.025f, -0.72f);
        glVertex2f(x + 0.025f, -0.72f);
        glVertex2f(x + 0.025f, -0.7f);
        glVertex2f(x - 0.025f, -0.7f);
        glEnd();

        // Arm extending from pole - steel color
        glColor3ub(180, 180, 185); // Light steel/silver
        glBegin(GL_QUADS);
        glVertex2f(x - 0.008f, -0.2f);
        glVertex2f(x + 0.15f, -0.2f);
        glVertex2f(x + 0.15f, -0.18f);
        glVertex2f(x - 0.008f, -0.18f);
        glEnd();

        // Light fixture (modern design) - smaller rectangle
        glColor3ub(200, 200, 205); // Brighter steel
        glBegin(GL_QUADS);
        glVertex2f(x + 0.13f, -0.21f);
        glVertex2f(x + 0.17f, -0.21f);
        glVertex2f(x + 0.17f, -0.17f);
        glVertex2f(x + 0.13f, -0.17f);
        glEnd();

        // Light glow (smaller but very bright)
        glColor3f(1.0f, 1.0f, 1.0f); // Very bright white
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + 0.15f, -0.19f);
        for(int j = 0; j <= 20; j++) {
            float angle = 2.0f * 3.14159f * j / 20;
            glVertex2f(x + 0.15f + cos(angle) * 0.04f, -0.19f + sin(angle) * 0.04f);
        }
        glEnd();

        // Additional realistic light elements
        // Light housing
        glColor3ub(60, 60, 60);
        glBegin(GL_QUADS);
        glVertex2f(x + 0.11f, -0.21f);
        glVertex2f(x + 0.19f, -0.21f);
        glVertex2f(x + 0.19f, -0.17f);
        glVertex2f(x + 0.11f, -0.17f);
        glEnd();

        // Light lens
        glColor3ub(200, 200, 180);
        glBegin(GL_QUADS);
        glVertex2f(x + 0.12f, -0.20f);
        glVertex2f(x + 0.18f, -0.20f);
        glVertex2f(x + 0.18f, -0.18f);
        glVertex2f(x + 0.12f, -0.18f);
        glEnd();
    }
}


void drawBuilding4(float x, float width, float height, int windowsX, int windowsY,
                  GLubyte r, GLubyte g, GLubyte b, float scale = 1.0f, float lineY = -0.12f) {

    float scaledHeight = height * scale;
    glPushMatrix();
    glTranslatef(x, lineY, 0.0f); // move bottom to lineY
    glScalef(scale, scale, 0.5f); // scale width & height
    glColor3ub(r/2, g/2, b/2); // Make buildings much darker
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(width, 0.0f);
        glVertex2f(width, height);
        glVertex2f(0.0f, height);
    glEnd();

    float windowWidth = width * 0.5f / windowsX;
    float windowHeight = height * 0.5f / windowsY;
    float spacingX = width * 0.1f / (windowsX + 1);
    float spacingY = height * 0.1f / (windowsY + 1);

    for(int i = 0; i < windowsX; i++) {
        for(int j = 0; j < windowsY; j++) {
            if((i + j) % 3 == 0) {
                glColor3ub(255, 255, 200); // Warm yellow light
            } else {
                glColor3ub(40, 50, 60); // Dark unlit window
            }
            float windowX = spacingX * (i+1) + windowWidth * i;
            float windowY = spacingY * (j+1) + windowHeight * j;

            glBegin(GL_QUADS);
                glVertex2f(windowX, windowY);
                glVertex2f(windowX + windowWidth, windowY);
                glVertex2f(windowX + windowWidth, windowY + windowHeight);
                glVertex2f(windowX, windowY + windowHeight);
            glEnd();

        }
    }
    glPopMatrix();
}

void urbanArea4() {
    float lineY = -0.12f; // baseline for buildings
    struct Building {
        float x, width, height;
        int windowsX, windowsY;
        GLubyte r, g, b;
        float scale;
    };

    Building buildings[] = {
        {-1.0f, 0.12f, 0.3f, 2, 3, 120, 120, 140, 0.5f},
        {-0.95f, 0.1f, 0.22f, 1, 2, 100, 120, 110, 0.5f},
        {-0.9f, 0.13f, 0.25f, 2, 3, 130, 120, 100, 0.5f},
        {-0.8f, 0.11f, 0.32f, 3, 4, 110, 130, 120, 0.5f},
        {-0.75f, 0.12f, 0.3f, 2, 3, 120, 110, 130, 0.5f},
        {-0.7f, 0.1f, 0.26f, 2, 3, 130, 120, 100, 0.5f},
        {-0.65f, 0.12f, 0.28f, 2, 4, 100, 120, 120, 0.5f},
        {-0.55f, 0.11f, 0.3f, 3, 4, 140, 130, 120, 0.5f},
        {-0.5f, 0.1f, 0.27f, 2, 3, 110, 120, 100, 0.5f},
        {-0.45f, 0.12f, 0.32f, 3, 5, 120, 110, 130, 0.5f},
        {-0.4f, 0.1f, 0.25f, 2, 3, 130, 120, 100, 0.5f},
        {-0.35f, 0.13f, 0.3f, 2, 4, 100, 120, 120, 0.5f},
        {-0.3f, 0.12f, 0.28f, 2, 3, 120, 100, 130, 0.5f},
        {-0.2f, 0.1f, 0.26f, 2, 3, 120, 110, 100, 0.5f},
        {-0.15f, 0.12f, 0.3f, 2, 4, 130, 120, 110, 0.5f},
        {-0.1f, 0.1f, 0.25f, 2, 3, 100, 120, 130, 0.5f},
        {-0.05f, 0.13f, 0.32f, 3, 5, 120, 100, 120, 0.5f},
        {0.0f, 0.1f, 0.28f, 2, 3, 130, 120, 100, 0.5f},
        {0.05f, 0.11f, 0.3f, 2, 4, 110, 130, 120, 0.5f},
        {0.1f, 0.12f, 0.26f, 2, 3, 120, 110, 130, 0.5f},
        {0.15f, 0.1f, 0.32f, 3, 4, 130, 120, 100, 0.5f},
        {0.2f, 0.12f, 0.3f, 2, 3, 100, 120, 120, 0.5f},
        {0.25f, 0.11f, 0.28f, 2, 4, 120, 100, 130, 0.5f},
        {0.3f, 0.1f, 0.25f, 2, 3, 110, 130, 120, 0.5f},
        {0.35f, 0.13f, 0.32f, 3, 5, 130, 120, 100, 0.5f},
        {0.4f, 0.12f, 0.3f, 2, 3, 120, 110, 130, 0.5f},
        {0.5f, 0.1f, 0.28f, 2, 3, 120, 100, 110, 0.5f},
        {0.55f, 0.12f, 0.3f, 2, 4, 130, 120, 100, 0.5f},
        {0.6f, 0.1f, 0.25f, 2, 3, 110, 130, 120, 0.5f},
        {0.65f, 0.13f, 0.32f, 3, 4, 120, 100, 130, 0.5f},
        {0.7f, 0.12f, 0.28f, 2, 3, 130, 120, 100, 0.5f},
        {0.75f, 0.1f, 0.3f, 2, 4, 100, 120, 120, 0.5f},
        {0.85f, 0.12f, 0.32f, 3, 5, 130, 120, 100, 0.5f},
        {0.9f, 0.1f, 0.28f, 2, 3, 110, 130, 120, 0.5f},
        {0.95f, 0.12f, 0.3f, 2, 4, 120, 100, 110, 0.5f}
    };

    int n = sizeof(buildings) / sizeof(buildings[0]);
    for(int i = 0; i < n; i++) {
        drawBuilding4(buildings[i].x, buildings[i].width, buildings[i].height,
                     buildings[i].windowsX, buildings[i].windowsY,
                     buildings[i].r, buildings[i].g, buildings[i].b,
                     buildings[i].scale, lineY);

    glColor3ub(150, 150, 150);
            glBegin(GL_LINES);
            glVertex2f(buildings[5].x + buildings[5].width/2 + (-0.005), lineY + buildings[5].height*buildings[5].scale);
            glVertex2f(buildings[5].x + buildings[5].width/2 + (-0.005), lineY + buildings[5].height*buildings[5].scale + 0.05f);
            glEnd();

            static float blinkTime = 0.0f;
            blinkTime += 0.016f;
            int blinkCycle = (int)(blinkTime / 40.0f);
            float cyclePosition = fmod(blinkTime, 40.0f); // Position within 40-second cycle

            if (cyclePosition < 20.0f) { // First 20 seconds - light ON
                glColor3f(1.0f, 0.0f, 0.0f); // Bright red
                drawFilledCircle(buildings[5].x + buildings[5].width/2 + (-0.005),
                               lineY + buildings[5].height*buildings[5].scale + 0.05f,
                               0.008f, 5);
            }
    }
}


void drawQuad(float x, float y, float w, float h) {
    float nx = toNormX(x);
    float ny = toNormY(y);
    float nw = toNormW(w);
    float nh = toNormH(h);

    glBegin(GL_QUADS);
    glVertex2f(nx, ny);
    glVertex2f(nx + nw, ny);
    glVertex2f(nx + nw, ny - nh);
    glVertex2f(nx, ny - nh);
    glEnd();
}

// Draw bridge towers with color arrays
void drawBridgeTowers(GLfloat color[3], GLfloat shadow_color[3]) {
    glColor3fv(shadow_color);
    drawQuad(407.8, 168, 13.5, 76.4);
    glColor3fv(color);
    drawQuad(407.8, 168, 9, 76.4);
    glColor3fv(shadow_color);
    drawQuad(449.9, 168, 13.5, 76.4);
    glColor3fv(color);
    drawQuad(449.9, 168, 9, 76.4);
    glColor3fv(color);
    drawQuad(407.8, 183.2, 55.6, 5.4);

    glColor3fv(shadow_color);
    drawQuad(396.5, 243.7, 17.4, 65.5);
    glColor3fv(color);
    drawQuad(396.5, 243.7, 11.6, 65.5);
    glColor3fv(shadow_color);
    drawQuad(450.8, 243.7, 17.4, 65.5);
    glColor3fv(color);
    drawQuad(450.8, 243.7, 11.6, 65.5);
    glColor3fv(color);
    drawQuad(396.5, 240.6, 71.7, 6.1);

    glColor3fv(shadow_color);
    drawQuad(386.1, 313.9, 22.4, 84.4);
    glColor3fv(color);
    drawQuad(386.1, 313.9, 15, 84.4);
    glColor3fv(shadow_color);
    drawQuad(456.1, 313.9, 22.4, 84.4);
    glColor3fv(color);
    drawQuad(456.1, 313.9, 15, 84.4);
    glColor3fv(color);
    drawQuad(386.1, 309, 92.5, 7.3);

    glColor3fv(shadow_color);
    drawQuad(372.7, 405, 28.9, 108.8);
    glColor3fv(color);
    drawQuad(372.7, 405, 19.3, 108.8);
    glColor3fv(shadow_color);
    drawQuad(463, 405, 28.9, 108.8);
    glColor3fv(color);
    drawQuad(463, 405, 19.3, 108.8);
    glColor3fv(color);
    drawQuad(372.7, 398.1, 119.2, 8.9);
}

void drawBezierCurve(float p0[2], float p1[2], float p2[2], GLfloat color[3], int segments = 50, float width = 2.0f) {
    glColor3fv(color);
    glLineWidth(width);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i <= segments; i++) {
        float t = i / (float)segments;
        float x_pixel = (1 - t)*(1 - t)*p0[0] + 2*(1 - t)*t*p1[0] + t*t*p2[0];
        float y_pixel = (1 - t)*(1 - t)*p0[1] + 2*(1 - t)*t*p1[1] + t*t*p2[1];

        // Convert to normalized coordinates
        float x_norm = toNormX(x_pixel);
        float y_norm = toNormY(y_pixel);
        glVertex2f(x_norm, y_norm);
    }
    glEnd();
}

void drawBridgeCables(GLfloat cableColor[3]) {
    float mainP0[2] = {459.7 + 19.3/2, 345};
    float mainP1[2] = {960, 550};
    float mainP2[2] = {1462 + 19.3/2, 345};
    drawBezierCurve(mainP0, mainP1, mainP2, cableColor, 100, 3.0f);

    float secP0[2] = {460.7 + 19.3/2, 245};
    float secP1[2] = {960, 650};
    float secP2[2] = {1460 + 19.3/2, 245};
    drawBezierCurve(secP0, secP1, secP2, cableColor, 100, 2.0f);

    float mainP02[2] = {1520.7 + 19.3/2, 345};
    float mainP12[2] = {2021, 550};
    float mainP22[2] = {2523 + 19.3/2, 445};
    drawBezierCurve(mainP02, mainP12, mainP22, cableColor, 100, 3.0f);

    float secP02[2] = {1521.7 + 19.3/2, 245};
    float secP12[2] = {2021, 650};
    float secP22[2] = {2521 + 19.3/2, 245};
    drawBezierCurve(secP02, secP12, secP22, cableColor, 100, 2.0f);

    float mainP03[2] = {-602.7 + 19.3/2, 345};
    float mainP13[2] = {-101, 550};
    float mainP23[2] = {399 + 19.3/2, 345};
    drawBezierCurve(mainP03, mainP13, mainP23, cableColor, 100, 3.0f);

    float secP03[2] = {-601.7 + 19.3/2, 245};
    float secP13[2] = {-101, 610};
    float secP23[2] = {399 + 19.3/2, 245};
    drawBezierCurve(secP03, secP13, secP23, cableColor, 100, 2.0f);

    // Draw vertical suspenders along the cables
    int segments = 100;
    for (int i = 0; i <= segments; i += 12) {
        float t = i / (float)segments;

        float x_main = (1 - t)*(1 - t)*mainP0[0] + 2*(1 - t)*t*mainP1[0] + t*t*mainP2[0];
        float y_main = (1 - t)*(1 - t)*mainP0[1] + 2*(1 - t)*t*mainP1[1] + t*t*mainP2[1]+20;

        float x_main2 = (1 - t)*(1 - t)*mainP02[0] + 2*(1 - t)*t*mainP12[0] + t*t*mainP22[0];
        float y_main2 = (1 - t)*(1 - t)*mainP02[1] + 2*(1 - t)*t*mainP12[1] + t*t*mainP22[1]+20;

        float x_main3 = (1 - t)*(1 - t)*mainP03[0] + 2*(1 - t)*t*mainP13[0] + t*t*mainP23[0];
        float y_main3 = (1 - t)*(1 - t)*mainP03[1] + 2*(1 - t)*t*mainP13[1] + t*t*mainP23[1]+20;

        float x_sec = (1 - t)*(1 - t)*secP0[0] + 2*(1 - t)*t*secP1[0] + t*t*secP2[0];
        float y_sec = (1 - t)*(1 - t)*secP0[1] + 2*(1 - t)*t*secP1[1] + t*t*secP2[1]+50;

        float x_sec2 = (1 - t)*(1 - t)*secP02[0] + 2*(1 - t)*t*secP12[0] + t*t*secP22[0];
        float y_sec2 = (1 - t)*(1 - t)*secP02[1] + 2*(1 - t)*t*secP12[1] + t*t*secP22[1]+50;

        float x_sec3 = (1 - t)*(1 - t)*secP03[0] + 2*(1 - t)*t*secP13[0] + t*t*secP23[0];
        float y_sec3 = (1 - t)*(1 - t)*secP03[1] + 2*(1 - t)*t*secP13[1] + t*t*secP23[1]+50;

        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glColor3fv(cableColor);

        // Convert to normalized coordinates
        glVertex2f(toNormX(x_main), toNormY(505));
        glVertex2f(toNormX(x_sec), toNormY(y_sec-45));

        glVertex2f(toNormX(x_main2), toNormY(505));
        glVertex2f(toNormX(x_sec2), toNormY(y_sec2-45));

        glVertex2f(toNormX(x_main3), toNormY(505));
        glVertex2f(toNormX(x_sec3), toNormY(y_sec3-45));
        glEnd();
    }
}

// Draw the whole bridge
void drawBridge(GLfloat bridge_color[3], GLfloat cables_color[3], GLfloat shadow_color[3]) {
    // cables
    drawBridgeCables(cables_color);

    // left towers
    drawBridgeTowers(bridge_color, shadow_color);

    // right towers (shifted)
    glPushMatrix();
    glTranslated(toNormW(1062), 0, 0);
    drawBridgeTowers(bridge_color, shadow_color);
    glPopMatrix();

    // base
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(0), toNormY(560));
    glVertex2f(toNormX(1920), toNormY(560));
    glVertex2f(toNormX(1920), toNormY(500));
    glVertex2f(toNormX(0), toNormY(500));
    glEnd();

    glBegin(GL_QUADS); // upper shadow
    glColor3fv(shadow_color);
    glVertex2f(toNormX(0), toNormY(510));
    glVertex2f(toNormX(1920), toNormY(510));
    glVertex2f(toNormX(1920), toNormY(500));
    glVertex2f(toNormX(0), toNormY(500));
    glEnd();

    // left pillar
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(325), toNormY(560));
    glVertex2f(toNormX(325), toNormY(585));
    glVertex2f(toNormX(415), toNormY(585));
    glVertex2f(toNormX(415), toNormY(560));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(350), toNormY(585));
    glVertex2f(toNormX(350), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(shadow_color);
    glVertex2f(toNormX(378), toNormY(585));
    glVertex2f(toNormX(378), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();

    glPushMatrix();
    glTranslated(toNormW(120), 0, 0);
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(325), toNormY(560));
    glVertex2f(toNormX(325), toNormY(585));
    glVertex2f(toNormX(415), toNormY(585));
    glVertex2f(toNormX(415), toNormY(560));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(350), toNormY(585));
    glVertex2f(toNormX(350), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(shadow_color);
    glVertex2f(toNormX(378), toNormY(585));
    glVertex2f(toNormX(378), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();
    glPopMatrix();

    // right pillars
    glPushMatrix();
    glTranslated(toNormW(1060), 0, 0);
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(325), toNormY(560));
    glVertex2f(toNormX(325), toNormY(585));
    glVertex2f(toNormX(415), toNormY(585));
    glVertex2f(toNormX(415), toNormY(560));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(350), toNormY(585));
    glVertex2f(toNormX(350), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(shadow_color);
    glVertex2f(toNormX(378), toNormY(585));
    glVertex2f(toNormX(378), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();

    glPushMatrix();
    glTranslated(toNormW(120), 0, 0);
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(325), toNormY(560));
    glVertex2f(toNormX(325), toNormY(585));
    glVertex2f(toNormX(415), toNormY(585));
    glVertex2f(toNormX(415), toNormY(560));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(bridge_color);
    glVertex2f(toNormX(350), toNormY(585));
    glVertex2f(toNormX(350), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();
    glBegin(GL_QUADS);
    glColor3fv(shadow_color);
    glVertex2f(toNormX(378), toNormY(585));
    glVertex2f(toNormX(378), toNormY(745));
    glVertex2f(toNormX(390), toNormY(745));
    glVertex2f(toNormX(390), toNormY(585));
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void drawBridgeByScene(int scene) {
    GLfloat bridge_color[3], cables_color[3], shadow_color[3];
    if (scene == 0) { // sunset
        toGLColorRGB(149, 36, 49, bridge_color);
        toGLColorRGB(190, 30, 45, cables_color);
        toGLColorRGB(182, 60, 74, shadow_color);
    }
    drawBridge(bridge_color, cables_color, shadow_color);
}

void drawFlyingBird(float x, float y, float scale = 1.0f, float wingOffset = 0.0f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3ub(119, 22, 24); // Dark color for silhouette

    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);

    // Bird profile
    glVertex2f(-0.05f, 0.0f);           // Beak tip
    glVertex2f(-0.1f, 0.02f);         // Head curve
    glVertex2f(-0.2f, 0.03f);         // Back of head
    glVertex2f(-0.25f, 0.02f);         // Upper back
    glVertex2f(-0.28f, 0.0f);          // Mid back


    glEnd();

     // Wing - filled triangle
    glBegin(GL_TRIANGLES);
    glColor3ub(119, 22, 24);     // Slightly lighter for wing
    glVertex2f(-0.15f, 0.01f);        // Wing base (attached to body)
    glVertex2f(-0.05f, 0.12f + wingOffset); // Wing tip (highest point)
    glVertex2f(-0.2f, 0.08f + wingOffset * 0.5f); // Wing back point
    glEnd();

    // Wing outline
    glLineWidth(1.2f);
    glBegin(GL_LINE_LOOP);
    glColor3ub(119, 22, 24);     // Dark outline
    glVertex2f(-0.15f, 0.01f);        // Wing base
    glVertex2f(-0.05f, 0.12f + wingOffset); // Wing tip
    glVertex2f(-0.2f, 0.08f + wingOffset * 0.5f); // Wing back
    glEnd();

    glPopMatrix();
}

float starCoords[50][2] = {
    {-0.85f, 0.92f}, {-0.12f, 0.78f}, {0.45f, 0.95f}, {-0.67f, 0.34f}, {0.23f, 0.56f},
    {0.89f, 0.82f}, {-0.95f, 0.15f}, {0.12f, 0.23f}, {-0.34f, 0.67f}, {0.76f, 0.45f},
    {-0.23f, -0.12f}, {0.56f, -0.34f}, {-0.78f, -0.56f}, {0.34f, -0.78f}, {-0.45f, -0.89f},
    {0.67f, -0.23f}, {-0.92f, -0.45f}, {0.15f, -0.67f}, {-0.56f, -0.12f}, {0.82f, -0.34f},
    {-0.15f, 0.45f}, {0.45f, 0.12f}, {-0.67f, 0.89f}, {0.23f, 0.34f}, {-0.89f, 0.56f},
    {0.34f, -0.12f}, {-0.12f, -0.34f}, {0.78f, -0.56f}, {-0.45f, -0.78f}, {0.56f, -0.89f},
    {-0.23f, 0.67f}, {0.67f, 0.23f}, {-0.34f, 0.45f}, {0.89f, 0.12f}, {-0.56f, 0.78f},
    {0.12f, -0.45f}, {-0.78f, -0.23f}, {0.45f, -0.67f}, {-0.89f, -0.34f}, {0.23f, -0.56f},
    {-0.67f, 0.12f}, {0.34f, 0.89f}, {-0.45f, 0.23f}, {0.56f, 0.67f}, {-0.12f, 0.34f},
    {0.78f, -0.12f}, {-0.23f, -0.78f}, {0.45f, -0.34f}, {-0.56f, -0.67f}, {0.67f, -0.89f}
};

void drawStars() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 50; i++) {
        glVertex2f(starCoords[i][0], starCoords[i][1]);
    }
    glEnd();
}

void sky(int scene) {
    float waterLevel = toNormY(740); // Water level at y=800 pixels
    if (scene == 0) { // Sunset
        // Gradient sunset sky
        glBegin(GL_QUADS);
        glColor3ub(215, 87, 75);  // Orange
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3ub(242, 163, 84);  // Pink-purple
        glVertex2f(1.0f, waterLevel);
        glVertex2f(-1.0f, waterLevel);
        glEnd();

        // Sun - solid inner circle3

    // Enable blending only for the outer glow circles
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Outer sun circle with transparency (blending effect)
    glColor4ub(243, 188, 123, 150); // Darker yellow with alpha
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.35f, -0.35f);  // Center of sun
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(0.35f + cos(angle) * 0.15f, -0.35f + sin(angle) * 0.15f);
    }
    glEnd();

    glColor4ub(243, 188, 123, 80); // Very transparent yellow
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.35f, -0.35f);  // Center of sun
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(0.35f + cos(angle) * 0.25f, -0.35f + sin(angle) * 0.25f);
    }
    glEnd();

    glDisable(GL_BLEND);


    // Solid inner circle (no transparency)
    glColor3ub(243, 235, 189); // Light yellow - solid color
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.35f, -0.35f);  // Center of sun
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(0.35f + cos(angle) * 0.1f, -0.35f + sin(angle) * 0.1f);
    }
    glEnd();
    drawStars();

    } else if (scene == 1) { // Night
        // Dark night sky
        glBegin(GL_QUADS);
        glColor3f(0.05f, 0.05f, 0.15f);  // Very dark blue
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3f(0.02f, 0.02f, 0.08f);  // Almost black
        glVertex2f(1.0f, waterLevel);
        glVertex2f(-1.0f, waterLevel);
        glEnd();

        // Stars
        glColor3f(1.0f, 1.0f, 1.0f);
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        for (int i = 0; i < 100; i++) {
            float x = (rand() % 2000 - 1000) / 1000.0f;
            float y = (rand() % 2000 - 1000) / 1000.0f;
            glVertex2f(x, y);
        }
        glEnd();

    } else { // Day
        // Gradient blue sky
        glBegin(GL_QUADS);
        glColor3f(0.53f, 0.81f, 0.92f);  // Light blue (top)
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3f(0.7f, 0.9f, 1.0f);    // Very light blue (bottom)
        glVertex2f(1.0f, waterLevel);
        glVertex2f(-1.0f, waterLevel);
        glEnd();
    }
}

void drawWater() {
    float waterLevel = toNormY(740); // your water height

    glBegin(GL_QUADS);

    // Bottom (deep water)
    glColor3ub(219, 80, 56);  // dark reddish-orange
    glVertex2f(-1.0f, -1.0f);       // Bottom-left
    glVertex2f( 1.0f, -1.0f);       // Bottom-right

    // Middle
    glColor3ub(236, 138, 48);  // medium orange
    glVertex2f( 1.0f, waterLevel - 0.25f);  // Top-right
    glVertex2f(-1.0f, waterLevel - 0.25f);  // Top-left

    glEnd();

    // Horizon glow (sun near water)
    glBegin(GL_QUADS);
    glColor3ub(252, 215, 130);   // bright orange near horizon
    glVertex2f(-1.0f, waterLevel - 0.25f);
    glVertex2f( 1.0f, waterLevel - 0.25f);
    glVertex2f( 1.0f, waterLevel);
    glVertex2f(-1.0f, waterLevel);
    glEnd();

    // Sunlight reflection (semi-transparent)
    glColor4ub(255, 200, 120, 180);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, waterLevel - 0.02f);
    glVertex2f( 0.5f, waterLevel - 0.02f);
    glVertex2f( 0.5f, waterLevel - 0.08f);
    glVertex2f(-0.5f, waterLevel - 0.08f);
    glEnd();
}

// (comet head)
void drawCometHead(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f); // bright white
    glVertex2f(x, y);
    int numSegments = 30;
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * 2.0f * 3.1415926f / numSegments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// Draw smooth fading tail
void drawCometTail(float x, float y, float speed, float angle) {
    float rad = angle * 3.1415926f / 180.0f;

    // Tail parameters
    float tailLength = 0.1f + speed * 10.0f;
    float tailWidth = cometRadius;

    // Tail points (triangle)
    // Tip is opposite to motion
    float tipX = x - tailLength * cos(rad);
    float tipY = y - tailLength * sin(rad);

    glBegin(GL_TRIANGLES);
    // Base points (attached to head)
    glColor3f(1.0f, 1.0f, 1.0f); // bright white
    glVertex2f(x + tailWidth * sin(rad), y - tailWidth * cos(rad)); // top side
    glVertex2f(x - tailWidth * sin(rad), y + tailWidth * cos(rad)); // bottom side
    // Tip point
    glColor3ub(228, 125, 77); // dim white
    glVertex2f(tipX, tipY);
    glEnd();
}


// rocks in the scene
void drawRocks() {
    // --- Left background rock ---
    glBegin(GL_POLYGON);
    glColor3ub(163, 41, 40);
    glVertex2f(-1.2f, -0.38f);
    glVertex2f(-0.85f, -0.38f);
    glVertex2f(-0.8f, -0.10f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(163, 41, 40);
    glVertex2f(-0.85f, -0.38f);
    glVertex2f(-0.55f, -0.38f);
    glVertex2f(-0.8f, -0.10f);
    glEnd();

    // --- Left background rock ---2
    glBegin(GL_POLYGON);
    glColor3ub(163, 41, 40);
    glVertex2f(-1.2+0.2f, -0.38f);
    glVertex2f(-0.85+0.2f, -0.38f);
    glVertex2f(-0.8+0.2f, -0.10f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(163, 41, 40);
    glVertex2f(-0.85+0.2f, -0.38f);
    glVertex2f(-0.55+0.2f, -0.38f);
    glVertex2f(-0.8+0.2f, -0.10f);
    glEnd();


    // --- Left background rock ---34
    glBegin(GL_POLYGON);
    glColor3ub(200, 82, 72);
    glVertex2f(-1.2+1.55f, -0.38f);
    glColor3ub(163, 41, 40);
    glVertex2f(-0.85+1.55f, -0.38f);
    glVertex2f(-0.8+1.55f, -0.10f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(163, 41, 40);
    glVertex2f(-0.85+1.55f, -0.38f);
    glVertex2f(-0.55+1.55f, -0.38f);
    glVertex2f(-0.8+1.55f, -0.10f);
    glEnd();

    // --- Left background rock ---2
    glBegin(GL_POLYGON);
    glColor3ub(163, 41, 40);
    glVertex2f(-1.2+1.90f, -0.28f);
    glVertex2f(-0.85+1.75f, -0.38f);
    glVertex2f(-0.8+1.75f, -0.10f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(163, 41, 40);
    glVertex2f(-0.85+1.75f, -0.38f);
    glVertex2f(-0.55+1.75f, -0.38f);
    glVertex2f(-0.55+1.75f, -0.10f);
    glVertex2f(-0.8+1.75f, -0.10f);
    glEnd();
}


void drawShadowCar() {
    float carWidth = 0.15f;
    float carHeight = 0.05f;
    float roofHeight = 0.03f;
    float wheelRadius = 0.015f;

    // --- Car body ---
    glColor3ub(30, 30, 30); // shadow color
    glBegin(GL_QUADS);
    glVertex2f(carX11, bridgeLevel);                        // bottom-left
    glVertex2f(carX11 + carWidth, bridgeLevel);             // bottom-right
    glVertex2f(carX11 + carWidth, bridgeLevel + carHeight); // top-right
    glVertex2f(carX11, bridgeLevel + carHeight);            // top-left
    glEnd();

    // --- Car roof (triangular) ---
    glBegin(GL_TRIANGLES);
    glVertex2f(carX11 + carWidth*0.25f, bridgeLevel + carHeight);       // left
    glVertex2f(carX11 + carWidth*0.75f, bridgeLevel + carHeight);       // right
    glVertex2f(carX11 + carWidth*0.5f, bridgeLevel + carHeight + roofHeight); // top
    glEnd();

    // --- Wheels ---
    glColor3ub(10, 10, 10); // darker shadow
    int numSegments = 20;
    float wheelOffsetX[2] = {0.03f, 0.12f};
    for (int i = 0; i < 2; i++) {
        float cx = carX11 + wheelOffsetX[i];
        float cy = bridgeLevel;
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy); // center
        for (int j = 0; j <= numSegments; j++) {
            float angle = j * 2.0f * M_PI / numSegments;
            float x = cx + cos(angle) * wheelRadius;
            float y = cy - sin(angle) * wheelRadius;
            glVertex2f(x, y);
        }
        glEnd();
    }

    // --- Update car position ---
    carX11 += carSpeed12;
    if (carX11 > 1.0f) carX11 = -1.2f; // Loop back
}


void drawBoat3ShadowWithSail() {
    float waterTop = -0.13f;
    float waterBottom = -0.72f;
    float waterCenterY = (waterTop + waterBottom) / 2.0f;

    glPushMatrix();
    glTranslatef(boatX, waterCenterY, 0.0f);
    glScalef(0.1f, 0.1f, 1.0f);

    // --- Main hull ---
    glColor3ub(119, 22, 24);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, -0.1f);
        glVertex2f(-0.8f,  0.2f);
        glVertex2f(-0.2f,  0.21f);
        glVertex2f(0.0f,  0.21f);
        glVertex2f(0.2f,  0.21f);
        glVertex2f(0.7f,  0.22f);
        glVertex2f(0.8f,  0.15f);
        glVertex2f(0.78f,  0.05f);
        glVertex2f(0.7f, -0.15f);
        glVertex2f(-0.6f, -0.15f);
    glEnd();

    // --- Inner strip ---
    glColor3ub(119, 22, 24);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f,  0.15f);
        glVertex2f(-0.2f,  0.2f);
        glVertex2f(0.7f,  0.18f);
        glVertex2f(0.75f, 0.12f);
        glVertex2f(-0.75f,  0.18f);
    glEnd();

    // --- Benches ---
    glColor3ub(119, 22, 24);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f,  0.2f);
        glVertex2f(0.0f,  0.13f);
        glVertex2f(0.1f,  0.13f);
        glVertex2f(0.1f,  0.2f);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(0.4f,  0.18f);
        glVertex2f(0.4f,  0.13f);
        glVertex2f(0.5f,  0.13f);
        glVertex2f(0.5f,  0.18f);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f,  0.18f);
        glVertex2f(-0.4f,  0.13f);
        glVertex2f(-0.5f,  0.13f);
        glVertex2f(-0.5f,  0.18f);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(0.2f, 1.8f);
        glVertex2f(0.2f, 0.0f);
        //glVertex2f(0.2f, 1.8f)
    glEnd();

    // --- Sail (raised above hull) ---
    glColor3ub(119, 22, 24); // shadow color
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 1.95f);    // top of sail (higher)
        glVertex2f(-0.45f, 0.4f);   // bottom left (above hull)
        glVertex2f(0.65f, 0.4f);    // bottom right
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(0.0+0.17f, 1.95f);    // top of sail (higher)
        glVertex2f(-0.45+0.17f, 0.4f);   // bottom left (above hull)
        glVertex2f(0.65+0.17f, 0.4f);    // bottom right
    glEnd();

    // --- Outline ---
    glColor3ub(119, 22, 24);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.7f, -0.1f);
        glVertex2f(-0.8f,  0.2f);
        glVertex2f(-0.2f,  0.21f);
        glVertex2f(0.0f,  0.21f);
        glVertex2f(0.2f,  0.21f);
        glVertex2f(0.7f,  0.21f);
        glVertex2f(0.8f,  0.15f);
        glVertex2f(0.78f,  0.05f);
        glVertex2f(0.7f, -0.15f);
        glVertex2f(-0.6f, -0.15f);
        glVertex2f(-0.7f, -0.1f);
    glEnd();

    glPopMatrix();
}

void drawMoon4(int r, int g, int b) {
    // Moon
    glColor3ub(r,g,b); // Silver-white moon
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.6f, 0.5f); // Center of circle
    for(int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.14159f * i / 100;
        glVertex2f(-0.6f + cos(angle) * 0.08f, 0.5f + sin(angle) * 0.08);
    }
    glEnd();
}

float starCoords3[50][2] = {
    {-0.85f, 0.92f}, {-0.12f, 0.78f}, {0.45f, 0.95f}, {-0.67f, 0.34f}, {0.23f, 0.56f},
    {0.89f, 0.82f}, {-0.95f, 0.15f}, {0.12f, 0.23f}, {-0.34f, 0.67f}, {0.76f, 0.45f},
    {-0.23f, -0.12f}, {0.56f, -0.34f}, {-0.78f, -0.56f}, {0.34f, -0.78f}, {-0.45f, -0.89f},
    {0.67f, -0.23f}, {-0.92f, -0.45f}, {0.15f, -0.67f}, {-0.56f, -0.12f}, {0.82f, -0.34f},
    {-0.15f, 0.45f}, {0.45f, 0.12f}, {-0.67f, 0.89f}, {0.23f, 0.34f}, {-0.89f, 0.56f},
    {0.34f, -0.12f}, {-0.12f, -0.34f}, {0.78f, -0.56f}, {-0.45f, -0.78f}, {0.56f, -0.89f},
    {-0.23f, 0.67f}, {0.67f, 0.23f}, {-0.34f, 0.45f}, {0.89f, 0.12f}, {-0.56f, 0.78f},
    {0.12f, -0.45f}, {-0.78f, -0.23f}, {0.45f, -0.67f}, {-0.89f, -0.34f}, {0.23f, -0.56f},
    {-0.67f, 0.12f}, {0.34f, 0.89f}, {-0.45f, 0.23f}, {0.56f, 0.67f}, {-0.12f, 0.34f},
    {0.78f, -0.12f}, {-0.23f, -0.78f}, {0.45f, -0.34f}, {-0.56f, -0.67f}, {0.67f, -0.89f}
};

void drawStars44() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 50; i++) {
        glVertex2f(starCoords3[i][0], starCoords3[i][1]);
    }
    glEnd();
}

void sky44(){
    // First rectangle (red)
    glColor3ub(114, 142, 164); // Red
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.2f);
        glVertex2f(1.0f, -0.2f);
        glColor3ub(32, 49, 83);
        glVertex2f(1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();
    drawStars44();

    // Second rectangle with blended color
    glBegin(GL_QUADS);
    // Top side (lighter blue)
    glColor3ub(69, 96, 131);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f( 1.0f, -0.2f);

    // Bottom side (darker blue)
    glColor3ub(38, 62, 101);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void tree(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);   // move tree position
    glScalef(scale, scale, 1.0f); // scale size (uniform)

    // Tree Trunk
    glColor3ub(31, 46, 77);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, -0.6f);
        glVertex2f( 0.02f, -0.6f);
        glVertex2f( 0.02f, -0.3f);
        glVertex2f(-0.02f, -0.3f);
    glEnd();

    // Pine Leaves (3 triangles)
    glColor3ub(31, 46, 77);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.15f, -0.3f);
        glVertex2f( 0.15f, -0.3f);
        glVertex2f( 0.0f, -0.1f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.12f, -0.2f);
        glVertex2f( 0.12f, -0.2f);
        glVertex2f( 0.0f,  0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.09f, -0.1f);
        glVertex2f( 0.09f, -0.1f);
        glVertex2f( 0.0f,  0.15f);
    glEnd();

    glPopMatrix();
}

void drawCircle(float cx, float cy, float r, int num_segments, int R, int G, int B) {
    glColor3ub(R, G, B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void tree2(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // --- Tree Trunk ---
    glColor3ub(30, 44, 76); // Brown trunk
    glBegin(GL_QUADS);
        glVertex2f(0.25f, -0.5f);
        glVertex2f(0.32f, -0.5f);
        glVertex2f(0.32f, -0.1f);
        glVertex2f(0.25f, -0.1f);
    glEnd();

    // --- Branches inside the crown ---
    glColor3ub(30, 44, 76); // dark brown branches
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        glVertex2f(0.22f, 0.0f);   glVertex2f(0.275f, -0.1f);
        glVertex2f(0.275f, -0.1f); glVertex2f(0.33f, 0.3f);
        glVertex2f(0.15f, 0.01f);   glVertex2f(0.275f, -0.2f);//3
        glVertex2f(0.275f, -0.2f); glVertex2f(0.46f, -0.06f);//2
        glVertex2f(0.275f, -0.18f); glVertex2f(0.4f, 0.2f);//1
    glEnd();
    glLineWidth(1.0f);

    // Tree Crown
    drawCircle(0.21f, 0.07f, 0.12f, 50, 31, 46, 77);
    drawCircle(0.24f, 0.13f, 0.1f, 50, 31, 46, 77);
    drawCircle(0.3f, 0.18f, 0.07f, 50, 31, 46, 77);
    drawCircle(0.26f, 0.15f, 0.1f, 50, 31, 46, 77);
    drawCircle(0.35f, 0.15f, 0.1f, 50, 31, 46, 77);
    drawCircle(0.37f, 0.13f, 0.1f, 50, 31, 46, 77);
    drawCircle(0.3f, 0.24f, 0.07f, 50, 31, 46, 77);
    drawCircle(0.15f, 0.14f, 0.07f, 50, 31, 46, 77);
    drawCircle(0.4f, 0.1f, 0.1f, 50, 31, 46, 77);

    drawCircle(0.47f, 0.0f, 0.06f, 50, 31, 46, 77);
    drawCircle(0.47f, 0.05f, 0.06f, 50, 31, 46, 77);
    drawCircle(0.47f, -0.05f, 0.06f, 50, 31, 46, 77);
    drawCircle(0.13f, 0.0f, 0.06f, 50, 31, 46, 77);
    drawCircle(0.13f, 0.05f, 0.06f, 50, 31, 46, 77);
    drawCircle(0.13f, -0.08f, 0.06f, 50, 31, 46, 77);
    glPopMatrix();
}

// Draw one blade with lattice-style lines
void drawLatticeBlade(float length, float width, int sections) {
    // Outline rectangle
    glBegin(GL_LINE_LOOP);
        glVertex2f(-width/2, 0.0f);
        glVertex2f( width/2, 0.0f);
        glVertex2f( width/2, length);
        glVertex2f(-width/2, length);
    glEnd();

    glLineWidth(3.0f);
    glBegin(GL_LINES);
        glVertex2f(width/2 -0.02, 0.0f);
        glVertex2f(width/2 -0.02, length);
    glEnd();
    glLineWidth(1.0f);

    glBegin(GL_LINES);
        glVertex2f(width/2 -0.06, 0.0f);
        glVertex2f(width/2 -0.06, length);
    glEnd();

    for (int i = 1; i < sections; i++) {
        float y = (length / sections) * i;
        glBegin(GL_LINES);
        if (i == 3) {
            // Make 3rd section smaller (shrink width by 30%)
            glVertex2f(-width/2, y);
            glVertex2f( width/2, y);
        } else {
            // Normal full width
            glVertex2f(-width/2, y+0.04);
            glVertex2f( width/2, y+0.04);
        }
        glEnd();
    }
}

// Draw circle hub at the center
void drawCircle(float cx, float cy, float r) {
    int num_segments = 40;
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / num_segments;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

// Full windmill fan
void drawWindmillFan(float cx, float cy, float angle) {
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);   // Move to fan center
    glRotatef(angle, 0.0f, 0.0f, 1.0f); // Rotation for animation

    glColor3ub(0, 0, 0); // Black blades

    // Draw 4 blades
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glRotatef(i * 90.0f, 0.0f, 0.0f, 1.0f);
        drawLatticeBlade(0.3f, 0.1f, 4); // length, width, number of sections
        glPopMatrix();
    }

    // Draw hub
    glColor3ub(40, 40, 40);
    drawCircle(0.0f, 0.0f, 0.03f);

    glPopMatrix();
}

// Small circle
void drawSmallCircle() {
    float cx = 0.49f;   // center x
    float cy = 0.46f;  // center y
    float r  = 0.02f;   // radius
    int num_segments = 50; // smoothness

    glColor3ub(52, 74, 94); // Same color as square
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawWindmill(){
    glColor3ub(29, 45, 77); // Dark gray hill
    glBegin(GL_POLYGON);
        glVertex2f(0.4f, -0.04f);
        glVertex2f(0.58f, -0.04f);
        glVertex2f(0.57f, 0.1f);
        glVertex2f(0.41f, 0.1f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.41f, 0.11f);
        glVertex2f(0.57f, 0.11f);
        glVertex2f(0.56f, 0.25f);
        glVertex2f(0.42f, 0.25f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.42f, 0.26f);
        glVertex2f(0.56f, 0.26f);
        glVertex2f(0.55f, 0.4f);
        glVertex2f(0.43f, 0.4f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.43f, 0.41f);
        glVertex2f(0.55f, 0.41f);
        glVertex2f(0.54f, 0.5f);
        glVertex2f(0.49f, 0.55f);
        glVertex2f(0.44f, 0.5f);
    glEnd();

    glColor3ub(252, 178, 27); // Square1
    glBegin(GL_POLYGON);
        glVertex2f(0.47f, -0.00f); // Bottom-left
        glVertex2f(0.51f, -0.00f); // Bottom-right
        glVertex2f(0.51f, 0.05f); // Top-right
        glVertex2f(0.47f, 0.05f); // Top-left
    glEnd();

    glColor3ub(252, 178, 27); // Square2
    glBegin(GL_POLYGON);
        glVertex2f(0.47f, 0.16f); // Bottom-left
        glVertex2f(0.51f, 0.16f); // Bottom-right
        glVertex2f(0.51f, 0.21f); // Top-right
        glVertex2f(0.47f, 0.21f); // Top-left
    glEnd();

    glColor3ub(252, 178, 27); // Square3
    glBegin(GL_POLYGON);
        glVertex2f(0.47f, 0.3f); // Bottom-left
        glVertex2f(0.51f, 0.3f); // Bottom-right
        glVertex2f(0.51f, 0.35f); // Top-right
        glVertex2f(0.47f, 0.35f); // Top-left
    glEnd();

    drawSmallCircle();

    glColor3ub(14, 30, 61); // line1
    glBegin(GL_POLYGON);
        glVertex2f(0.41f, 0.1f);
        glVertex2f(0.57f, 0.1f);
        glVertex2f(0.57f, 0.11f);
        glVertex2f(0.41f, 0.11f);
    glEnd();

    glColor3ub(14, 30, 61); // line2
    glBegin(GL_POLYGON);
        glVertex2f(0.42f, 0.25f);
        glVertex2f(0.56f, 0.25f);
        glVertex2f(0.56f, 0.26f);
        glVertex2f(0.42f, 0.26f);
    glEnd();

    glColor3ub(14, 30, 61); // line3
    glBegin(GL_POLYGON);
        glVertex2f(0.43f, 0.4f);
        glVertex2f(0.55f, 0.4f);
        glVertex2f(0.55f, 0.41f);
        glVertex2f(0.43f, 0.41f);
    glEnd();
}

void drawHill(int R, int G, int B) {
    // Dark Hill
    glColor3ub(R, G, B); // Dark gray hill
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -0.2f);   // Left bottom
        glVertex2f(-1.0f, -0.1f);
        glVertex2f(-0.9f, -0.07f);
        glVertex2f(-0.8f, -0.07f);
        glVertex2f(-0.7f, -0.05f);
        glVertex2f(-0.65f, -0.1f);
        glVertex2f(-0.55f, -0.1f);
        glVertex2f(-0.50f, -0.15f);
        glVertex2f(-0.1f, -0.1f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.4f, -0.04f);
        glVertex2f(0.8f, -0.04f);
        glVertex2f(0.9f, -0.04f);
        glVertex2f(1.0f, -0.01f);
        glVertex2f(1.0f, -0.2f);    // Right bottom
    glEnd();
}
void drawFence(float startX, float endX, float yBottom, float yTop) {
    // --- Horizontal Bars ---
    glColor3ub(15, 30, 58); // Dark brown
    glBegin(GL_QUADS);
        // Bottom bar
        glVertex2f(startX, yBottom);
        glVertex2f(endX, yBottom);
        glVertex2f(endX, yBottom + 0.02f);
        glVertex2f(startX, yBottom + 0.02f);

        // Top bar
        glVertex2f(startX, yTop);
        glVertex2f(endX, yTop);
        glVertex2f(endX, yTop + 0.02f);
        glVertex2f(startX, yTop + 0.02f);
    glEnd();

    // --- Vertical Posts ---
    float spacing = 0.08f; // distance between posts
    for (float x = startX; x <= endX; x += spacing) {
        glBegin(GL_QUADS);
            glVertex2f(x - 0.01f, yBottom);
            glVertex2f(x + 0.01f, yBottom);
            glVertex2f(x + 0.01f, yTop + 0.05f); // taller than top bar
            glVertex2f(x - 0.01f, yTop + 0.05f);
        glEnd();
    }
}


void drawHut(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // --- Hut Base (Rectangle) ---
    glColor3ub(28, 45, 74); // Light brown for walls
    glBegin(GL_QUADS);
        glVertex2f(0.0f, -0.3f); // Bottom-left
        glVertex2f( 0.2f, -0.3f); // Bottom-right
        glVertex2f( 0.2f,  0.1f); // Top-right
        glVertex2f(0.0f,  0.1f); // Top-left
    glEnd();

    // --- Roof (Triangle) ---
    glColor3ub(17, 32, 62); // Dark brown for roof
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.1f); // Left corner
        glVertex2f( 0.25f, 0.1f); // Right corner
        glVertex2f( 0.18f,  0.25f); // Top peak
        glVertex2f( 0.0f,  0.25f); // Top peak
    glEnd();


    // --- Window (Small Square) ---
    glColor3ub(253, 180, 23); // Light blue for glass
    glBegin(GL_QUADS);
        glVertex2f(0.05f, -0.15f); // Bottom-left
        glVertex2f(0.13f, -0.15f); // Bottom-right
        glVertex2f(0.13f, -0.05f); // Top-right
        glVertex2f(0.05f, -0.05f); // Top-left
    glEnd();

    // Window cross
    glColor3ub(15, 30, 58); // Window frame
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        // Horizontal line
        glVertex2f(0.05f, -0.1f);
        glVertex2f(0.13f, -0.1f);
        // Vertical line
        glVertex2f(0.09f, -0.15f);
        glVertex2f(0.09f, -0.05f);
    glEnd();
    glLineWidth(1.0f);
    //drawFence(x , x - 0.1f, y - 0.3f, y - 0.15f); // Left fence
    drawFence(x + 0.2f, x + 0.78f, y - 0.3f, y - 0.15f); // Right fence

    glPopMatrix();
}


// (comet head)
void drawCometHead44(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f); // bright white
    glVertex2f(x, y);
    int numSegments = 30;
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * 2.0f * 3.1415926f / numSegments;
        glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();
}

// Draw smooth fading tail
void drawCometTail44(float x, float y, float speed, float angle) {
    float rad = angle * 3.1415926f / 180.0f;

    // Tail parameters
    float tailLength = 0.1f + speed * 10.0f;
    float tailWidth = cometRadius3;

    // Tail points
    // Tip is opposite to motion
    float tipX = x - tailLength * cos(rad);
    float tipY = y - tailLength * sin(rad);

    glBegin(GL_TRIANGLES);
    // Base points (attached to head)
    glColor3f(1.0f, 1.0f, 1.0f); // bright white
    glVertex2f(x + tailWidth * sin(rad), y - tailWidth * cos(rad)); // top side
    glVertex2f(x - tailWidth * sin(rad), y + tailWidth * cos(rad)); // bottom side
    // Tip point
    glColor3ub(228, 125, 77); // dim white
    glVertex2f(tipX, tipY);
    glEnd();
}

void boat4() {
    float waterTop = 0.3f;
    float waterBottom = -0.72f;
    float waterCenterY = (waterTop + waterBottom) / 2.0f;

    glPushMatrix();
    glTranslatef(boatX3, waterCenterY, 0.0f);
    glScalef(0.1f, 0.1f, 1.0f);

    glColor3ub(30, 20, 15);
    glBegin(GL_LINES);
        glVertex2f(-0.4f, 1.0f);
        glVertex2f(-0.4f, 0.0f);
    glEnd();

    // --- Main hull ---
    glColor3ub(30, 20, 15);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f, -0.1f);
        glVertex2f(-0.8f,  0.2f);
        glVertex2f(-0.2f,  0.21f);
        glVertex2f(0.0f,  0.21f);
        glVertex2f(0.2f,  0.21f);
        glVertex2f(0.7f,  0.22f);
        glVertex2f(0.8f,  0.15f);
        glVertex2f(0.78f,  0.05f);
        glVertex2f(0.7f, -0.15f);
        glVertex2f(-0.6f, -0.15f);
    glEnd();

    // --- Inner strip ---
    glColor3ub(145, 106, 67);
    glBegin(GL_POLYGON);
        glVertex2f(-0.7f,  0.15f);
        glVertex2f(-0.2f,  0.2f);
        glVertex2f(0.7f,  0.18f);
        glVertex2f(0.75f, 0.12f);
        glVertex2f(-0.75f,  0.18f);
    glEnd();

    // --- Benches ---
    glColor3ub(188, 149, 58);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f,  0.2f);
        glVertex2f(0.0f,  0.13f);
        glVertex2f(0.1f,  0.13f);
        glVertex2f(0.1f,  0.2f);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(0.4f,  0.18f);
        glVertex2f(0.4f,  0.13f);
        glVertex2f(0.5f,  0.13f);
        glVertex2f(0.5f,  0.18f);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f,  0.18f);
        glVertex2f(-0.4f,  0.13f);
        glVertex2f(-0.5f,  0.13f);
        glVertex2f(-0.5f,  0.18f);
    glEnd();

    // --- Outline ---
    glColor3ub(14, 30, 61);
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.7f, -0.1f);
        glVertex2f(-0.8f,  0.2f);
        glVertex2f(-0.2f,  0.21f);
        glVertex2f(0.0f,  0.21f);
        glVertex2f(0.2f,  0.21f);
        glVertex2f(0.7f,  0.21f);
        glVertex2f(0.8f,  0.15f);
        glVertex2f(0.78f,  0.05f);
        glVertex2f(0.7f, -0.15f);
        glVertex2f(-0.6f, -0.15f);
        glVertex2f(-0.7f, -0.1f);
    glEnd();

    glPopMatrix();
}


void drawScene1() {
    glClear(GL_COLOR_BUFFER_BIT);

    sky();
    Sun();
    glLoadIdentity();
    // Move and rotate plane
    glPushMatrix();
    glTranslatef(planeX, planeY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glScalef(0.1f, 0.1f, 1.0f);
    drawSimpleAirplane();
    glPopMatrix();
    Cloud(cloudX+0.5, 0.8f, 0.1f);
    Cloud(cloudX+0.9f, 0.85f, 0.08f);
    Cloud(cloudX+1.4f, 0.75f, 0.12f);
    Cloud(cloudX-1.0f, 0.75f, 0.12f);
    Cloud(cloudX-0.5f, 0.85f, 0.08f);
    Cloud(cloudX-1.6f, 0.75f, 0.12f);
    Ground();
    urbanArea(); // Draw buildings first
    MetroOverpass(); // Draw metro overpass in front of buildings
    draw2DCar();
    drawTruck(); // Add the truck to the scene
    glFlush();
}

void drawScene4() {
    glClear(GL_COLOR_BUFFER_BIT);
    sky4();
    drawStars4();
    drawMoon4();
    Cloud4(cloudX+0.7f, 0.8f, 0.1f);
    Cloud4(cloudX+1.4f, 0.85f, 0.08f);
    Ground4();
    drawStreetLights4(); // Add street lights
    urbanArea4(); // Draw buildings first
    MetroOverpass4(); // Draw metro overpass in front of buildings
    draw2DCar4();
    drawTruck4(); // Add the truck to the scene
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFlush();
}

void drawScene12() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int currentScene = 0;
    // Draw background elements with time parameter
    sky(currentScene);
        // Draw multiple birds at different scales
    float wingOffset = sin(birdWingFlap) * 0.1f;

    drawFlyingBird(birdX, birdY, 0.1f, wingOffset);
    drawFlyingBird(birdX - 0.3f, birdY - 0.2f, 0.1f, wingOffset + 0.05f);
    drawFlyingBird(birdX + 0.5f, birdY + 0.1f, 0.1f, wingOffset - 0.05f);
    drawWater();
    drawCometTail(cometX, cometY, cometSpeed+0.02, cometAngle);
    drawCometHead(cometX, cometY, cometRadius);
    drawCometTail(cometX, cometY+0.5, cometSpeed+0.02, cometAngle);
    drawCometHead(cometX, cometY+0.5, cometRadius);
    // Move comet
    drawRocks();
    drawShadowCar();
    drawBridgeByScene(currentScene);
    drawBoat3ShadowWithSail();
    glFlush();
}

float fanAngle = 0.0f; // global rotation angle
void drawScene13() {
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    sky44();
    drawCometTail44(comet3X, comet3Y, cometSpeed3+0.02, cometAngle3);
    drawCometHead44(comet3X, comet3Y, cometRadius3);
    drawHill(50,50,50);
    drawWindmillFan(0.49f, 0.46f, fanAngle);
    drawWindmill();
    tree(-0.5f, -0.03f, 0.15f);
    tree(-0.8f, -0.01f, 0.15f);
    tree(-0.6f, -0.01f, 0.15f);
    tree(0.59f, 0.015f, 0.15f);
    tree(0.82f, 0.03f, 0.15f);
    tree2(-0.75f, -0.015f, 0.10f);
    tree2(0.74f, -0.01f, 0.10f);
    tree2(-0.03f, 0.04f, 0.10f);
    tree2(-0.3f, -0.01f, 0.10f);
    tree2(-0.2f, -0.01f, 0.10f);
    tree2(-0.23f, -0.01f, 0.10f);
    tree(-0.15f, 0.03f, 0.15f);
    drawHut(0.04f, 0.04f, 0.17f);

    // REFLECTION
    // Enable stencil buffer for reflection
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF);
    // Draw water area as stencil mask
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glBegin(GL_QUADS);
        glColor3f(0.239f, 0.345f, 0.494f);
        glVertex2f(-1.0f, -0.2f);
        glVertex2f( 1.0f, -0.2f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    // Set up stencil for reflection
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilMask(0x00);
    // Enable blending for reflection
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Draw reflected scene
    glPushMatrix();
    glScalef(1.0f, -1.0f, 1.0f); // Mirror vertically
    glTranslatef(0.0f, 0.4f, 0.0f); // Adjust position
    // Reduce opacity for reflection
    glColor4f(1.0f, 1.0f, 1.0f, 0.01f);
    tree(-0.5f, -0.03f, 0.15f);
    tree(-0.8f, -0.01f, 0.15f);
    tree(-0.6f, -0.01f, 0.15f);
    tree(0.59f, 0.015f, 0.15f);
    tree(0.82f, 0.03f, 0.15f);
    tree2(-0.75f, -0.015f, 0.10f);
    tree2(0.74f, -0.01f, 0.10f);
    tree2(-0.03f, 0.04f, 0.10f);
    tree2(-0.3f, -0.01f, 0.10f);
    tree2(-0.2f, -0.01f, 0.10f);
    tree2(-0.23f, -0.01f, 0.10f);
    tree(-0.15f, 0.03f, 0.15f);
    drawHut(0.04f, 0.04f, 0.17f);
    drawCometTail(comet3X, comet3Y, cometSpeed3+0.02, cometAngle3);
    drawCometHead(comet3X, comet3Y, cometRadius3);
    drawHill(37,58,95);
    drawMoon4(149, 165, 184);
    drawWindmillFan(0.49f, 0.46f, fanAngle);
    drawWindmill();
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_STENCIL_TEST);

    drawMoon4(254, 254, 254);
    boat4();
    glFlush();
}


void update(int value) {
    trainOffset1 -= trainSpeed;       // move left
    if (trainOffset1 < -2.2f)         // if train goes past left edge
        trainOffset1 = 2.2f;          // wrap to right

    trainOffset2 += trainSpeed;       // move right
    if (trainOffset2 > 2.2f)          // if train goes past right edge
        trainOffset2 = -2.2f;         // wrap to left

    carPosX += carSpeed; // move car to the right
    if (carPosX > 1.5f)  // reset when it goes off screen
        carPosX = -1.5f;

    cloudX += cloudSpeed;
    if (cloudX > 1.5f) {
        cloudX = -1.5f;
    }

    fanAngle += 1.0f;  // increase rotation speed (degrees per frame)
    if (fanAngle > 360) fanAngle -= 360; // keep in range

    // Update comet position
    comet3X += cometSpeed3 * cos(cometAngle3 * 3.1415926f / 180.0f);
    comet3Y += cometSpeed3 * sin(cometAngle3 * 3.1415926f / 180.0f);

    // Reset comet if it goes off screen
    if (comet3X > 1.5f || comet3Y > 1.5f || comet3X < -1.5f || comet3Y < -0.2f) {
        comet3X = -1.0f;
        comet3Y = 1.0f;
    }

    planeX += speed;
    planeY += speed * 0.6f; // Upward component
    if (planeX > 2.0f) { // Reset position when it goes off-screen
        planeX = -1.5f;
        planeY = -0.4f;
    }


    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void updateComet() {
    float rad = cometAngle * 3.1415926f / 180.0f;
    cometX += cometSpeed * cos(rad);
    cometY += cometSpeed * sin(rad);

    // Reset if out of screen
    if (cometX > 1.1f || cometY > 1.1f) {
        cometX = -1.0f;
        cometY = 0.0f;
    }

    glutPostRedisplay();
}

void updateBird() {
    birdX += birdSpeed;
    birdWingFlap += 0.001f;

    // Reset bird position when it flies off screen
    if (birdX > 1.5f) {
        birdX = -1.5f;
        birdY = 0.3f + (rand() % 100) / 200.0f; // Random height
    }

    // Add some vertical movement for realism
    birdY += sin(birdWingFlap) * 0.000001f;
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    if (currentScene == 1) {
        drawScene1();
    }else if (currentScene == 2) {
        drawScene4();
    }else if (currentScene == 3) {
        drawScene12();
    }
    else if (currentScene == 4) {
        drawScene13();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == '1') currentScene = 1; // go to Scene 1
    if (key == '2') currentScene = 2;
    if (key == '3') currentScene = 3;
    if (key == '4') currentScene = 4;
    if (key == 27) exit(0);           // ESC to quit

    if (key == 'a' || key == 'A') {
        boatX -= boatSpeed; // Move left
        if (boatX < -1.0f) boatX = -1.0f; // Prevent leaving screen
    }
    if (key == 'd' || key == 'D') {
        boatX += boatSpeed; // Move right
        if (boatX > 1.0f) boatX = 1.0f; // Prevent leaving screen
    }
    glutPostRedisplay(); // refresh the display
}

// Idle function
void idle() {
    updateComet();
    updateBird();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Dhaka Metro Train in Urban Landscape");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // Sky blue background
    glutTimerFunc(0, update, 0);
    glutIdleFunc(idle);

    glutMainLoop();
    return 0;
}
