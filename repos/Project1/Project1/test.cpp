#include <iostream> 

#include <Windows.h> 
#include <GL\glew.h> 
#include <GL\freeglut.h>


const int MAX_LENGTH = 100;

int WindowWidth = 1024;    
int WindowHeight = 1024;    
int k, n;  
float moveX = -2.5, moveY = -1.8, moveZ = -3.0;
int xRotation = 0, yRotation = 0;

float di = 0.5; 
float a = 2.0;

typedef struct {
    float x;
    float y;
    float z;
    int node_x;
    int node_y;
    int node_z;
    int node_num;
}Node;

struct Cycle2d {
    Node left;
    Node top;
    Node right;
    Node bottom;
    struct Cycle2d* left_cycle; // ¶‘¤‚Ìnode‚ÉŒq‚ª‚Á‚Ä‚¢‚é\‘¢‘ÌCycle2d‚ðŽQÆ‚·‚é‚½‚ß‚ÌéŒ¾
    struct Cycle2d* top_cycle;
    struct Cycle2d* right_cycle;
    struct Cycle2d* bottom_cycle;
};

struct Cycle3d {
    Node left;
    Node top_left;
    Node top_right;
    Node right;
    Node bottom_right;
    Node bottom_left;
    struct Cycle3d* left_cycle; // ¶‘¤‚Ìnode‚ÉŒq‚ª‚Á‚Ä‚¢‚é\‘¢‘ÌCycle3d‚ðŽQÆ‚·‚é‚½‚ß‚ÌéŒ¾
    struct Cycle3d* top_left_cycle;
    struct Cycle3d* top_right_cycle;
    struct Cycle3d* right_cycle;
    struct Cycle3d* bottom_right_cycle;
    struct Cycle3d* bottom_left_cycle;
};

Node node[MAX_LENGTH][MAX_LENGTH];
Cycle2d cycle2d[MAX_LENGTH][MAX_LENGTH];
Cycle3d cycle3d[MAX_LENGTH][MAX_LENGTH][MAX_LENGTH];

void createSphere(Node *node) {
    glPushMatrix();
    glTranslatef(node->x, node->y, node->z);
    glColor3f(0.1, 0.75, 0.1);
    glutSolidSphere(0.05, 20.0, 20.0);
    glPopMatrix();
}

void createLineOnCycle(Node *start_node, Node *end_node) {
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(start_node->x, start_node->y, start_node->z);
    glVertex3f(end_node->x, end_node->y, end_node->z);
    glEnd();
}

//void createLineForConnection(Node *start_node, Node *end_node) {
//    GLfloat ctrlpoints[3][3] = {
//    {start_node->x, start_node->y, start_node->z},
//    {(start_node->x + end_node->x) / 2, (start_node->y + end_node->y) / 2.0 - 1.0, (start_node->z + end_node->z) / 2.0},
//    {end_node->x, end_node->y, end_node->z},
//    };
//    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[0][0]);
//    glEnable(GL_MAP1_VERTEX_3);
//    GLfloat white[] = { 0.0, 1.0, 1.0, 1.0 };
//    glColor4fv(&white[0]);
//    glBegin(GL_LINE_STRIP);
//    for (int i = 0; i <= 30; i++)
//        glEvalCoord1f((GLfloat)i / 30.0);
//    glEnd();
//}

void createLine(float startX, float startY, float startZ, float endX, float endY, float endZ) {
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex3f(startX, startY, startZ); 
    glVertex3f(endX, endY, endZ);
    glEnd();
}

void createAxis() {
    glColor3f(1, 0, 0); 
    createLine(-1000.0, 0, 0, 1000.0, 0, 0); 

    glColor3f(0, 0, 1);
    createLine(0, -1000.0, 0, 0, 1000.0, 0);

    glColor3f(1, 1, 1); 
}

void printnumber(int number) {
    int digits = 0;
    int number_for_digits = number;
    do {
        number_for_digits /= 10;
        digits++;
    } while (number_for_digits != 0);

    for (digits; digits > 0; digits--) {
        int index = 1;
        for (int i = 1; i < digits; i++) {
            index *= 10;
        }
        int number_of_digits = number / index;
        char numbers[] = { '0','1','2','3','4','5','6','7','8','9' };
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, numbers[number_of_digits]);
        number -= number_of_digits * index;
    }
}

void printFor2d(Node *node) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(node->x - 0.25, node->y + 0.1, node->z);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '(');
    printnumber(node->node_x);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ',');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    printnumber(node->node_y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ',');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    printnumber(node->node_num);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ')');
}

void printFor3d(Node* node) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos3f(node->x - 0.25, node->y + 0.1, node->z);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '(');
    printnumber(node->node_x);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ',');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    printnumber(node->node_y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ',');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    printnumber(node->node_z);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ',');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
    printnumber(node->node_num);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ')');
}

void create2dCycle(Cycle2d* cycle) {
    createSphere(&cycle->left); 
    printFor2d(&cycle->left);

    createSphere(&cycle->top); 
    printFor2d(&cycle->top);

    createSphere(&cycle->bottom);
    printFor2d(&cycle->bottom);

    createSphere(&cycle->right);
    printFor2d(&cycle->right);

    createLineOnCycle(&cycle->left, &cycle->top); 
    createLineOnCycle(&cycle->top, &cycle->right); 
    createLineOnCycle(&cycle->right, &cycle->bottom);
    createLineOnCycle(&cycle->bottom, &cycle->left); 
}

void create2dConnection(Cycle2d *cycle) {
    if (cycle->left.node_x + 1 != k) {
        createLineOnCycle(&cycle->left, &cycle->left_cycle->bottom);
    }
    else if (cycle->left.node_x + 1 == k) {
        Node end_node = { cycle->bottom.x + a, cycle->bottom.y, cycle->bottom.z };
        createLineOnCycle(&cycle->left, &end_node);
    }
    if (cycle->left.node_x == 0) {
        Node end_node = { cycle->left.x - a, cycle->left.y, cycle->left.z };
        createLineOnCycle(&cycle->bottom, &end_node);
    }

    if (cycle->right.node_y + 1 != k) {
        createLineOnCycle(&cycle->right, &cycle->right_cycle->top);
    }
    else if (cycle->right.node_y + 1 == k) {
        Node end_node = { cycle->top.x, cycle->top.y + a, cycle->top.z };
        createLineOnCycle(&cycle->right, &end_node);
    }
    if (cycle->right.node_y == 0) {
        Node end_node = { cycle->right.x, cycle->right.y - a, cycle->right.z };
        createLineOnCycle(&cycle->top, &end_node);
    }
}

void create2dTCC(float x, float y, float z) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            Node init_node = Node{ x + (j * a), y + (i * a), z, j, i, 0, 0 };
            cycle2d[i][j] = Cycle2d{
                init_node, // left
                Node{init_node.x + di, init_node.y + di, init_node.z, j, i, 0, 1}, // top
                Node{init_node.x + (di * 2), init_node.y, init_node.z, j, i, 0, 2}, // right
                Node{init_node.x + di, init_node.y - di, init_node.z, j, i, 0, 3}, // bottom
            };
            create2dCycle(&cycle2d[i][j]);
        }
    }

    for (int i = 0; i < k; i++) {   
        for (int j = 0; j < k; j++) {
            if (j + 1 < k){
                cycle2d[i][j].left_cycle = &cycle2d[i][j + 1];
                cycle2d[i][j + 1].bottom_cycle = &cycle2d[i][j];
            }
            else {
                cycle2d[i][j].left_cycle = &cycle2d[i][0];
                cycle2d[i][0].bottom_cycle = &cycle2d[i][j];
            }

            if (i + 1 < k){
                cycle2d[i][j].right_cycle = &cycle2d[i + 1][j];
                cycle2d[i + 1][j].top_cycle = &cycle2d[i][j];
            }
            else {
                cycle2d[i][j].right_cycle = &cycle2d[0][j];
                cycle2d[0][j].right_cycle = &cycle2d[i][j];
            }
            create2dConnection(&cycle2d[i][j]);
        }
    }
}

void create3dCycle(Cycle3d *cycle) {
    createSphere(&cycle->left); // left
    printFor3d(&cycle->left);
    createSphere(&cycle->top_left); // top-left
    printFor3d(&cycle->top_left);
    createSphere(&cycle->top_right); // top-right
    printFor3d(&cycle->top_right);
    createSphere(&cycle->right); // right
    printFor3d(&cycle->right);
    createSphere(&cycle->bottom_right); // bottom-right
    printFor3d(&cycle->bottom_right);
    createSphere(&cycle->bottom_left); // bottom-left
    printFor3d(&cycle->bottom_left);

    createLineOnCycle(&cycle->left, &cycle->top_left); 
    createLineOnCycle(&cycle->top_left, &cycle->top_right);
    createLineOnCycle(&cycle->top_right, &cycle->right);
    createLineOnCycle(&cycle->right, &cycle->bottom_right);
    createLineOnCycle(&cycle->bottom_right, &cycle->bottom_left);
    createLineOnCycle(&cycle->bottom_left, &cycle->left);
}

void create3dConnection(Cycle3d *cycle) {
    //createLineForConnection(&cycle->left, &cycle->left_cycle->top_left);
    //createLineForConnection(&cycle->top_right, &cycle->top_right_cycle->right);
    //createLineForConnection(&cycle->bottom_right, &cycle->bottom_right_cycle->bottom_left);
    if (cycle->left.node_y + 1 != k) {
        createLineOnCycle(&cycle->left, &cycle->left_cycle->top_left);
    }
    else if (cycle->left.node_y + 1 == k) {
        Node end_node = Node{ cycle->top_left.x, cycle->top_left.y + a, cycle->top_left.z };
        createLineOnCycle(&cycle->left, &end_node);
    }
    if (cycle->left.node_y == 0) {
        Node end_node = Node{ cycle->left.x, cycle->left.y - a, cycle->left.z };
        createLineOnCycle(&cycle->top_left, &end_node);
    }

    if (cycle->top_right.node_z + 1 != k)
        createLineOnCycle(&cycle->top_right, &cycle->top_right_cycle->right);
    else if (cycle->top_right.node_z + 1 == k) {
        Node end_node = Node{ cycle->right.x, cycle->right.y, cycle->right.z - a };
        createLineOnCycle(&cycle->top_right, &end_node);
    }
    if (cycle->top_right.node_z == 0) {
        Node end_node = Node{ cycle->top_right.x, cycle->top_right.y, cycle->top_right.z + a };
        createLineOnCycle(&cycle->right, &end_node);
    }
}

void create3dTCC(float x, float y, float z) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            for (int m = 0; m < k; m++) {
                Node init_node = Node{ x + (m * a), y + (j * a), z - (i * a), m, j, i, 0 }; // left
                    cycle3d[i][j][m] = Cycle3d{
                    init_node,
                    Node{init_node.x + di, init_node.y + di, init_node.z, m, j, i, 1}, // top-right
                    Node{init_node.x + (di * 2), init_node.y + di, init_node.z, m, j, i, 2}, // top-left
                    Node{init_node.x + (di * 3), init_node.y, init_node.z, m, j, i, 3}, // right
                    Node{init_node.x + (di * 2), init_node.y - di, init_node.z, m, j, i, 4}, // bottom-right
                    Node{init_node.x + di, init_node.y - di, init_node.z, m, j, i, 5}, // bottom-left
                };
                create3dCycle(&cycle3d[i][j][m]);
            }
        }
    }

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            for (int m = 0; m < k; m++) {
                if (j + 1 < k) {
                    cycle3d[i][j][m].left_cycle = &cycle3d[i][j + 1][m];
                    cycle3d[i][j + 1][m].top_left_cycle = &cycle3d[i][j][m];
                }
                else {
                    cycle3d[i][j][m].left_cycle = &cycle3d[i][0][m];
                    cycle3d[i][0][m].top_left_cycle = &cycle3d[i][j][m];
                }
                if (m + 1 < k) {
                    cycle3d[i][j][m].bottom_right_cycle = &cycle3d[i][j][m + 1];
                    cycle3d[i][j][m + 1].bottom_left_cycle = &cycle3d[i][j][m];
                }
                else {
                    cycle3d[i][j][m].bottom_right_cycle = &cycle3d[i][j][0];
                    cycle3d[i][j][0].bottom_left_cycle = &cycle3d[i][j][m];
                }
                if (i + 1 < k) {
                    cycle3d[i][j][m].top_right_cycle = &cycle3d[i + 1][j][m];
                    cycle3d[i + 1][j][m].right_cycle = &cycle3d[i][j][m];
                }
                else {
                    cycle3d[i][j][m].top_right_cycle = &cycle3d[0][j][m];
                    cycle3d[0][j][m].right_cycle = &cycle3d[i][j][m];
                }
                create3dConnection(&cycle3d[i][j][m]);
            }
        }
    }
}

void display2d(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glTranslatef(moveX, moveY, moveZ);
    glRotatef(yRotation, 0, 1.0, 0);
    glRotatef(xRotation, 1.0, 0, 0);
    createAxis();

    create2dTCC(0.6, 1.0, 0);

    glPopMatrix();

    glFlush();
}

void display3d(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(moveX, moveY, moveZ);
    glRotatef(yRotation, 0, 1.0, 0);
    glRotatef(xRotation, 1.0, 0, 0);
    createAxis();

    create3dTCC(0.6, 1.0, 0);

    glPopMatrix();
    glFlush();
}

void keyboardFunctions(unsigned char key, int a, int b) {
    switch (key) {
        case 'h':
            moveX += 0.1;
            break;
        case 'l':
            moveX -= 0.1;
            break;
        case 'k':
            moveY -= 0.1;
            break;
        case 'j':
            moveY += 0.1;
            break;
        case 'u':
            moveZ += 0.4;
            break;
        case 'i':
            moveZ -= 0.4;
            break;
        case 't':
            yRotation += 5;
            break;
        case 'y':
            yRotation -= 5;
            break;
        case 'v':
            xRotation += 5;
            break;
        case 'b':
            xRotation -= 5;
            break;
    }
    glutPostRedisplay();
}

void initialize(void) {
    glViewport(0, 0, WindowWidth, WindowHeight);
    glEnable(GL_DEPTH_TEST);

    gluPerspective(30.0,                                       
        (double)WindowWidth / (double)WindowHeight, 
        0.1,                                        
        1200);                                      

    gluLookAt(0.0, 0.0, 10.0, 
        0.0, 0.0, 0.0,  
        0.0, 1.0, 0.0); 
}

void resize(int w, int h) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, (double)w / (double)h, 0.1, 1200);
    glViewport(0, 0, w, h);
    gluLookAt(0.0, 0.0, 10.0,
        0.0, 0.0, 0.0,
        0.0, 0.1, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void judge2dOr3d() {
    if (n == 2) {
        glutDisplayFunc(display2d);
    }
    else if (n == 3) {
        glutDisplayFunc(display3d);
    }
}

int main(int argc, char** argv) {

    printf("k = ");
    scanf_s("%d", &k);
    while (true){
        printf("n = ");
        scanf_s("%d", &n);
        if (n == 2 || n == 3) break;
        else printf("Please enter the number 2 or 3 (2d or 3d)\n");
    }

    glutInit(&argc, argv);
    glutInitWindowPosition(500, 100);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("We love TCC!");
    initialize(); 
    judge2dOr3d();
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboardFunctions);
    glutMainLoop();
    return 0;
}
