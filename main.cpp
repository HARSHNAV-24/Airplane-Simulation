#include <graphics.h>
#include <conio.h>
#include <dos.h>

class Runway {
public:
    void drawRunway() {
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, DARKGRAY);
        rectangle(0, 350, 640, 450);
        floodfill(10, 360, WHITE);

        // Runway center line
        setcolor(WHITE);
        for (int i = 0; i < 640; i += 40)
            rectangle(i, 395, i + 20, 405);
    }
};

class Plane {
protected:
    int x, y;
    int color;
public:
    Plane(int xPos, int yPos, int c) {
        x = xPos; y = yPos; color = c;
    }

    virtual void drawPlane() {
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        // Plane body
        rectangle(x, y, x + 80, y + 20);
        floodfill(x + 1, y + 1, color);
        // Nose
        line(x + 80, y, x + 100, y + 10);
        line(x + 80, y + 20, x + 100, y + 10);
        // Tail
        line(x, y, x - 10, y - 10);
        line(x, y + 20, x - 10, y + 30);
    }

    virtual void movePlane() {
        for (int i = 0; i < 400; i += 5) {
            cleardevice();
            Runway r;
            r.drawRunway();
            drawPlane();
            delay(30);
            x += 5;
        }
    }
};

class PassengerPlane : public Plane {
public:
    PassengerPlane(int xPos, int yPos, int c) : Plane(xPos, yPos, c) {}

    void movePlane() override {
        // Acceleration + takeoff
        for (int i = 0; i < 300; i += 5) {
            cleardevice();
            Runway r;
            r.drawRunway();
            drawPlane();
            delay(25);
            x += 5;
            if (i > 150) y -= 2; // plane lifts off
        }
    }
};

class CargoPlane : public Plane {
public:
    CargoPlane(int xPos, int yPos, int c) : Plane(xPos, yPos, c) {}

    void movePlane() override {
        // Slower takeoff
        for (int i = 0; i < 300; i += 4) {
            cleardevice();
            Runway r;
            r.drawRunway();
            drawPlane();
            delay(35);
            x += 4;
            if (i > 200) y -= 2;
        }
    }
};

void drawSky() {
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    rectangle(0, 0, 640, 350);
    floodfill(1, 1, LIGHTBLUE);

    // Clouds
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(100, 100, 30, 20);
    fillellipse(130, 100, 30, 20);
    fillellipse(160, 100, 30, 20);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    drawSky();
    Runway runway;
    runway.drawRunway();

    PassengerPlane p1(50, 380, YELLOW);
    CargoPlane c1(0, 420, GREEN);

    outtextxy(200, 200, "AIRPORT RUNWAY SIMULATION");
    delay(2000);

    cleardevice();
    drawSky();
    runway.drawRunway();
    outtextxy(50, 50, "Passenger Plane Taking Off...");
    p1.movePlane();

    cleardevice();
    drawSky();
    runway.drawRunway();
    outtextxy(50, 50, "Cargo Plane Taking Off...");
    c1.movePlane();

    outtextxy(200, 200, "Simulation Complete!");
    getch();
    closegraph();
    return 0;
}
