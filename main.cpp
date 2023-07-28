#include<graphics.h>
#include<iostream>

using namespace std;


class SpaceShooter{
private:
    int screenWidth, screenHeight, centerX, centerY;
    int totalMenuItems = 2;
    int selectedMenuItem = 1;
    string enabledMenuType = "NONE";

public:
    SpaceShooter(int width = 600, int height = 800){
        screenWidth = width;
        screenHeight = height;
        centerX = width/2;
        centerY = height/2;
    }

    void start(){

        initwindow(screenWidth,screenHeight,"Space Shooter",150,50);

//        showPreloader();
        showMenu();
        listenMenuSelection();



        getch();
        closegraph();
    }

private:
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

    void showMenu(string type = "startMenu"){
        int menuItemHeight = 60;

        // set selected menu in globally
        enabledMenuType = type;

        cleardevice();
        setcolor(COLOR(0,247,6));
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);

        int itemXPos = centerX - 60, itemYPos = centerY - 100;
        outtextxy(itemXPos, itemYPos + (menuItemHeight * 0), "START");
        outtextxy(itemXPos, itemYPos + (menuItemHeight * 1), "EXIT");

        // Draw the selection arrow
        setcolor(COLOR(247,0,0));
        outtextxy(centerX - 100, centerY - 100 + ((selectedMenuItem - 1) * menuItemHeight), ">");

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
        cout << selectedMenuItem << endl;
        showMenu();
    }

    void upKeyAction(){
        toggleMenuItem("UP");
    }
    void downKeyAction(){
        toggleMenuItem("DOWN");
    }
    void enterKeyAction(){

    }

    void listenMenuSelection() {
        int choice = 1;
        while(true) {
            if(GetAsyncKeyState(VK_UP)) {
                upKeyAction();
            } else if(GetAsyncKeyState(VK_DOWN)) {
                downKeyAction();
            } else if(GetAsyncKeyState(VK_RETURN)) {
            }
            delay(100);
        }
    }

    // Functions Execution
    void Function_Execution(int choice, int Theme) {
        if(choice == 1) {
            cleardevice();
            setcolor(LIGHTGREEN);
            settextstyle(0, HORIZ_DIR, 4);
            outtextxy(150, 250, "COMING SOON...");
            //        PlaySound(TEXT("res/select_option.wav"),NULL,SND_SYNC);
//            Esc_Theme(1, Theme);
        }
        if(choice == 2) {
            cleardevice();
//            Game_Interface(Theme);
//            Multiplayer(Theme);
        }
        if(choice == 3) {
            cleardevice();
            if(Theme == 1) {
                readimagefile("res/menu_controls1.jpg", 250, 20, 450, 50);
                readimagefile("res/menucontrols1.jpg", 210 + 10, 80, 490 - 10, 200);
                readimagefile("res/game_controls1.jpg", 250, 250, 450, 280);
                readimagefile("res/gamecontrols1.jpg", 120, 300 + 10, 580, 330);
                readimagefile("res/other_controls1.jpg", 260, 380, 440, 410);
                readimagefile("res/othercontrols1.jpg", 210 - 10, 440, 490 + 10, 560);
            }
            if(Theme == 2) {
                readimagefile("res/menu_controls2.jpg", 250, 20, 450, 50);
                readimagefile("res/menucontrols2.jpg", 210, 80, 490, 200);
                readimagefile("res/game_controls2.jpg", 250, 250, 450, 280);
                readimagefile("res/gamecontrols2.jpg", 120, 300 + 10, 580, 330);
                readimagefile("res/other_controls2.jpg", 260, 380, 440, 410);
                readimagefile("res/othercontrols2.jpg", 210 - 10, 440, 490 + 10, 560);
            }
            //        PlaySound(TEXT("res/select_option.wav"),NULL,SND_SYNC);
//            Esc_Theme(3, Theme);
        }
        if(choice == 4) {
            int page = 0;
            //        PlaySound(TEXT("res/select_option.wav"),NULL,SND_SYNC);
            cleardevice();
            for(int i = 100; i < 1200; i++) {
                setfillstyle(SOLID_FILL, BLACK);
                if(Theme == 1) {
                    readimagefile("res/title1.jpg", 50, 620 - i, 650, 730 - i);
                    readimagefile("res/about_g.jpg", 50, 800 - i, 650, 1320 - i);
                    bar(50, 1320 - i, 650, 2000 - i);
                }
                if(Theme == 2) {
                    readimagefile("res/title2.jpg", 50, 620 - i, 650, 730 - i);
                    readimagefile("res/about_b.jpg", 50, 800 - i, 650, 1320 - i);
                    bar(50, 1320 - i, 650, 2000 - i);
                }
                if(GetAsyncKeyState(VK_ESCAPE)) {
                    break;
                }
                if(GetAsyncKeyState(VK_F6)) {
                    Function_Execution(4, 1);
                    //            PlaySound(TEXT("res/select_option.wav"),NULL,SND_SYNC);
                }
                if(GetAsyncKeyState(VK_F7)) {
                    Function_Execution(4, 2);
                    //            PlaySound(TEXT("res/select_option.wav"),NULL,SND_SYNC);
                }
                page = 1 - page;
                delay(1);
            }
//            showMenu(Theme);
            //         PlaySound(TEXT("res/select_option.wav"),NULL,SND_SYNC);
            listenMenuSelection();
        }
        if(choice == 5) {
            cleardevice();
            if(Theme == 1) {
                readimagefile("res/quitmsg1.jpg", 50, 200, 650, 250);
                readimagefile("res/yes1.jpg", 100 + 50, 300 + 10, 170 + 50, 330 + 10);
                readimagefile("res/no1.jpg", 530 - 50, 300 + 10, 600 - 50, 330 + 10);
            }
            if(Theme == 2) {
                readimagefile("res/quitmsg2.jpg", 50, 200, 650, 250);
                readimagefile("res/yes2.jpg", 100 + 50, 300 + 10, 170 + 50, 330 + 10);
                readimagefile("res/no2.jpg", 530 - 50, 300 + 10, 600 - 50, 330 + 10);
            }
            //        PlaySound(TEXT("res/select_option.wav"),NULL,SND_SYNC);
//            Quit(Theme);
        }
    }



};




int main() {

     SpaceShooter game(600,800);

     game.start();

}




