#include<graphics.h>
#include<iostream>

using namespace std;


class SpaceShooter{
private:
    int screenWidth, screenHeight, centerX, centerY;
    int totalMenuItems = 2;
    int selectedMenuItem = 1;
    string selectedMenu = "startMenu"; // startMenu, pausedMenu, none

    int n_Gun = 0;
    int shipSpeed = 4;
    int y = 30, m = y * 2;
    int gunPts[1024];
    int shipW = 70, shipH = 80;
    int shipPos[4] = {
        0,
        0,
        0,
        0,
    };
    int objectPts[81] = {
        40,
        100,
        70,
        100 - y,
        100,
        100,
        130,
        100 - y,
        160,
        100,
        190,
        100 - y,
        220,
        100,
        250,
        100 - y,
        280,
        100,
        310,
        100 - y,
        340,
        100,
        370,
        100 - y,
        400,
        100,
        430,
        100 - y,
        460,
        100,
        490,
        100 - y,
        520,
        100,
        280,
        50,
        40,
        100 - y * 3 - 20,
        70,
        100 - y * 4 - 20,
        100,
        100 - y * 3 - 20,
        130,
        100 - y * 4 - 20,
        160,
        100 - y * 3 - 20,
        190,
        100 - y * 4 - 20,
        220,
        100 - y * 3 - 20,
        250,
        100 - y * 4 - 20,
        280,
        100 - y * 3 - 20,
        310,
        100 - y * 4 - 20,
        340,
        100 - y * 3 - 20,
        370,
        100 - y * 4 - 20,
        400,
        100 - y * 3 - 20,
        430,
        100 - y * 4 - 20,
        460,
        100 - y * 3 - 20,
        490,
        100 - y * 4 - 20,
        520,
        100 - y * 3 - 20
    };

public:
    SpaceShooter(int width = 600, int height = 800){
        screenWidth = width;
        screenHeight = height;
        centerX = width/2;
        centerY = height/2;

        shipPos[0] = centerX - (shipW/2);
        shipPos[1] = screenHeight - 200 + shipH;
        shipPos[2] = centerX + (shipW/2);
        shipPos[3] = screenHeight - 200;
    }

    void start(){

        initwindow(screenWidth,screenHeight,"Space Shooter",150,50);

//        showPreloader();
//        showMenu();

        startGame();

        getch();
        closegraph();
    }

private:

    // show preloader
    void showPreloader(){
        int logoH = 100, logoW = 100;
        int progressH = 10, progressW = 100;
        int logoProgressGap = 20;

        readimagefile("assets/logo.jpg",centerX-(logoW/2),centerY-logoH,centerX+(logoW/2),centerY);
        rectangle(centerX-progressW/2,centerY+logoProgressGap,centerX+progressW/2,centerY+logoProgressGap+progressH);
        setcolor(CYAN);
        for(int i=0;i<=progressW-2;i++){
            line(centerX-(progressW/2-1)+i,centerY+logoProgressGap+1,centerX-(progressW/2-1)+i,centerY+logoProgressGap+progressH-1);
            delay(10);
        }
        cleardevice();
    }

    // show menu
    void showMenu(string type = "startMenu"){
        // set selected menu in globally
        selectedMenu = type;

        if(selectedMenu == "startMenu" || selectedMenu == "pausedMenu"){
            drawMenu();
            listenMenuSelection();
        }

    }
    void drawMenu(){
        int menuItemHeight = 60;
        cleardevice();
        setcolor(COLOR(0,247,6));
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);

        int itemXPos = centerX - 60, itemYPos = centerY - 100;

        outtextxy(itemXPos, itemYPos + (menuItemHeight * 0), "START");
        outtextxy(itemXPos, itemYPos + (menuItemHeight * 1), "EXIT");

        // Draw the selection arrow
        setcolor(COLOR(0,255,240));
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(itemXPos - 40, itemYPos + 5 + ((selectedMenuItem - 1) * menuItemHeight), ">");

        //help text
        setcolor(COLOR(0,247,6));
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        outtextxy(70, centerY + 300 , "(Up) (Down) arrow for navigation");
        outtextxy(110, centerY + 320 , "\n(Enter) for go to the menu");
    }

    // Menu Selector
    void toggleMenuItem(string actionKey = "UP") {
        if(actionKey == "UP"){
            selectedMenuItem = (selectedMenuItem == 1) ? totalMenuItems : (selectedMenuItem - 1);
        }else{
            selectedMenuItem = (selectedMenuItem % totalMenuItems) + 1;
        }
        drawMenu();
    }

    // listen keyboard button up, down, enter for action for menu. finally delay 100 ms for long press issue handle
    void listenMenuSelection() {
        while(true) {
            if(selectedMenu != "startMenu" && selectedMenu != "pausedMenu"){
                break;
            }
            if(GetAsyncKeyState(VK_UP)) {
                cout << "up pressed" << endl;
                toggleMenuItem("UP");
            } else if(GetAsyncKeyState(VK_DOWN)) {
                cout << "down pressed" << endl;
                toggleMenuItem("DOWN");
            } else if(GetAsyncKeyState(VK_RETURN)) {
                cout << "enter pressed" << endl;
                if(selectedMenuItem == 1){
                    startGame();
                }else if(selectedMenuItem == 2){
                    closegraph();
                }
            }
            delay(100);
        }
    }

    void startGame(){
        selectedMenu = "none";
        cleardevice();
        while(1){

            if(GetAsyncKeyState(VK_RIGHT)){
//                if(shipPts[6] < 630){
//                    for(int i = 0 ; i < 24 ; i = i + 2){
//                        shipPts[i]+=shipSpeed;
//                    }
//                }
            }else if(GetAsyncKeyState(VK_LEFT)){
//                if(shipPts[16] > 0){
//                    for(int i = 0 ; i < 24 ; i = i + 2){
//                        shipPts[i]-=shipSpeed;
//                    }
//                }
            }

            drawShip();


            delay(40);
            cleardevice();
        }
//        drawGun();

    }

    void drawShip(){
        readimagefile("assets/spaceShip.jpg",shipPos[0],shipPos[1],shipPos[2],shipPos[3]);
    }

//    void drawGun(){
//        if(objectPts[35]>0){
//            int length = shipPts[1] - 20;
//            float del_X = shipPts[0] - 280 ;
//            del_X = del_X/length;
//            int del_Y = 1;
//
//            for(int i = 0,j=0 ; i < n_Gun ; i ++,j=j+2){
//                setcolor(RED);
//               // floodfill(gunPts[j],gunPts[j+1],RED);
//                circle(gunPts[j],gunPts[j+1],5);
//                gunPts[j] += del_X*5;
//                gunPts[j+1] += del_Y*5;
//            }
//        }
//    }



};




int main() {

     SpaceShooter game(600,800);

     game.start();

}




