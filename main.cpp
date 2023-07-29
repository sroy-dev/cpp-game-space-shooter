#include<graphics.h>
#include<iostream>

using namespace std;


class SpaceShooter{
private:
    int screenWidth, screenHeight, centerX, centerY;
    int totalMenuItems = 2;
    int selectedMenuItem = 1;
    string selectedMenu = "startMenu"; // startMenu, pausedMenu, none

    int y = 30, m = y * 2;
    int n_BossBullets = 0;
    int bossBulletsPos[1024];

    int bulletgap = 30;
    int bulletPos[1024];
    int n_bullet = 0;


    int shipSpeed = 8;
    int shipW = 70, shipH = 80;
    int shipPos[4] = {
        0,
        0,
        0,
        0,
    };

    int score = 0;
    int isRunnig = 0;
    int life = 5;
    int isGameOver = 0;

    int safeLine = 0;
    int totalEnemyShip = 17*2+1;
    int boss_hp = 5;


    int temp=0;
    int enemyShipSpeed = 5;
    int enemyShipsPos[81] = {
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

        safeLine = screenHeight - 200 + shipH;

        shipPos[0] = centerX - (shipW/2);
        shipPos[1] = screenHeight - 120;
        shipPos[2] = centerX + (shipW/2);
        shipPos[3] = screenHeight - 120 + shipH;
    }

    void start(){

        initwindow(screenWidth,screenHeight,"Space Shooter",150,50);

        showPreloader();
        showMenu();

//        startGame();

        getch();
        closegraph();
    }

private:

    // show preloader
    void showPreloader(){
        int logoH = 100, logoW = 88;
        int progressH = 10, progressW = 100;
        int logoProgressGap = 20;

        readimagefile("assets/spaceShip.jpg",centerX-(logoW/2),centerY-logoH,centerX+(logoW/2),centerY);
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

            if(isGameOver){
                break;
            }

            if(GetAsyncKeyState(VK_RIGHT)){
                if(shipPos[2] < this->screenWidth){
                    shipPos[0]+=shipSpeed;
                    shipPos[2]+=shipSpeed;
                }
            }else if(GetAsyncKeyState(VK_LEFT)){
                if(shipPos[0] > 0){
                    shipPos[0]-=shipSpeed;
                    shipPos[2]-=shipSpeed;
                }
            }else if(GetAsyncKeyState(VK_SPACE)){
                bulletPos[n_bullet*2] = shipPos[0] + 35; //x-coordinate same as ship center pt
                bulletPos[n_bullet*2+1] = shipPos[1] - 20;//y-coordinate
                n_bullet++;
                n_bullet = n_bullet%1024;
            }

            //Boss Firing bullets
            int r = rand()%100;
            if(enemyShipsPos[35]>0){
                r = rand()%100;
                if(r>95){
                    bossBulletsPos[n_BossBullets*2] = 300; //x-coordinate same as ship center pt
                    bossBulletsPos[n_BossBullets*2+1] = 60;//y-coordinate
                    n_BossBullets++;
                    n_BossBullets = n_BossBullets%1024;
                }
            }

            drawShip();
            drawBullets();

            drawEnemyShips();
            drawBossBullets();

            checkBulletCollision();
            checkBossBulletsCollision();
            setfillstyle(SOLID_FILL,BLACK);
            drawScore(score);
            drawLife();

//            cout << "-----" <<endl;

            delay(40);
            cleardevice();
        }

        char msg[20];
        if(isGameOver == 1) {
            snprintf(msg, sizeof(msg), "Your Score:%d", score);
            while(1) {
                setcolor(GREEN);
                settextstyle(8, HORIZ_DIR, 1);
                outtextxy(240, 200, "You Won");
                setcolor(WHITE);
                outtextxy(240, 220, msg);
                outtextxy(240, 240, "Press ESC to Exit");
                if(GetAsyncKeyState(VK_ESCAPE)) {
//                    closegraph();
                    return;
                }
                delay(40);
                cleardevice();
            }
        } else {
            snprintf(msg, sizeof(msg), "Your Score:%d", score);
            while(1) {
                setcolor(RED);
                settextstyle(8, HORIZ_DIR, 1);
                outtextxy(240, 200, "Game Over");
                setcolor(WHITE);
                outtextxy(240, 220, msg);
                outtextxy(240, 240, "Press ESC to Exit");
                if(GetAsyncKeyState(VK_ESCAPE)) {
//                    closegraph();
                    return;
                }
                delay(60);
                cleardevice();
            }
        }

    }

    void drawShip(){
        readimagefile("assets/spaceShip.jpg",shipPos[0],shipPos[1],shipPos[2],shipPos[3]);
    }

    void drawBullets(){
        setcolor(YELLOW);
        for(int i = 0, j=0 ; i < n_bullet ; i++, j=j+2){
//            readimagefile("assets/bullet.jpg",bulletPos[j]-3,bulletPos[j+1],bulletPos[j]+3,bulletPos[j+1]+12);
            rectangle(bulletPos[j]-2,bulletPos[j+1],bulletPos[j]+2,bulletPos[j+1]+8);
            bulletPos[j+1] -= bulletgap;
//            cout << bulletPos[i] << endl;
        }
    }

    void drawEnemyShips(){
        for(int i = 0,j=0 ; i < 17*2+1; i++,j = j + 2){
            if(i==17){
//                readimagefile("assets/enemy.jpg",enemyShipsPos[j],enemyShipsPos[j+1],enemyShipsPos[j]+40,enemyShipsPos[j+1]+40);//for filled rectangle
                setfillstyle(SOLID_FILL,RED);
                bar(enemyShipsPos[j],enemyShipsPos[j+1],enemyShipsPos[j]+40,enemyShipsPos[j+1]+40);//for filled rectangle
            }else{
//                readimagefile("assets/enemy.jpg",enemyShipsPos[j],enemyShipsPos[j+1],enemyShipsPos[j]+20,enemyShipsPos[j+1]+20);//for filled rectangle

                setfillstyle(SOLID_FILL,WHITE);
                bar(enemyShipsPos[j],enemyShipsPos[j+1],enemyShipsPos[j]+20,enemyShipsPos[j+1]+20);//for filled rectangle
            }
            if(temp==20){
                if(i!=17){
                    enemyShipsPos[j+1] += enemyShipSpeed;
                }
            }
        }
        if(temp==20){
            temp=0;
        }
        temp++;
    }

    void drawBossBullets(){
        if(enemyShipsPos[35]>0){
//            int length = 400;
//            float del_X = 50 ;
            int length = shipPos[1] - 20;
            float del_X = shipPos[0] - 265 ;
//            cout << del_X << " " << length << endl;
            del_X = del_X/length;
            int del_Y = 1;

//            cout << del_X << " " << length << endl;

            for(int i = 0,j=0 ; i < n_BossBullets ; i ++,j=j+2){
                setcolor(RED);
                circle(bossBulletsPos[j],bossBulletsPos[j+1],5);
                bossBulletsPos[j] += del_X*5;
                bossBulletsPos[j+1] += del_Y*7;
            }
        }
    }

    void drawScore(int score){
        setcolor(YELLOW);
        char scoreResult[10];
        settextstyle(9,HORIZ_DIR,1);
        sprintf(scoreResult,"Score: %d",score);
        outtextxy(screenWidth - 150,screenHeight - 30,scoreResult);
    }

    void drawLife(){
        setcolor(YELLOW);
        char lifeResult[10];
        sprintf(lifeResult, "Life:  %d", life*100/5);
        outtextxy(10,screenHeight - 30,lifeResult);
    }


    void checkBulletCollision(){
        int width = 20;
        if(totalEnemyShip<=0){
            isGameOver = 1;
        }
        for(int i = 0,a=0 ; i < 17*2+1 ;i++,a=a+2){
            if(enemyShipsPos[a+1]>=safeLine-20){
                isGameOver=2;
            }
            for(int j = 0,k=0 ; j < n_bullet ; j++,k=k+2){
                if(bulletPos[k+1]>0){
                    if(a==34){
                        width = 40;
                    }else{
                        width = 20;
                    }
                    if(enemyShipsPos[a]<=bulletPos[k] && bulletPos[k]<=enemyShipsPos[a]+width){
                        if(enemyShipsPos[a+1]<=bulletPos[k+1] && bulletPos[k+1]<=enemyShipsPos[a+1]+width){
                            if(a==34 && boss_hp!=0){
                                score=score+10;
                                boss_hp--;
                                bulletPos[k+1]=-1000;
                                // enemyShipsPos[a+1]=-1000;
                            }
                            else{
                                enemyShipsPos[a+1] = -1000;
                                bulletPos[k+1] = -1000;
                                score = score + 10;
                                totalEnemyShip--;
                            }

                        }
                    }
                }
            }
        }
    }

    void checkBossBulletsCollision(){
        for(int j = 0,k=0 ; j < n_BossBullets ; j++,k=k+2){
            if(bossBulletsPos[k+1]>0){
                // inside ship x pos check
                if(shipPos[0]<=bossBulletsPos[k] && shipPos[2]>=bossBulletsPos[k]){
                    // inside ship y position
                    if(shipPos[1]<=bossBulletsPos[k+1] && shipPos[3]>=bossBulletsPos[k+1]){
//                        cout << shipPos[1] << " " << bossBulletsPos[k+1] << endl;
                        life--;
                        bossBulletsPos[k+1]=screenHeight + 500;
                        if(life==0){
                            isGameOver = 2;
                        }
                    }
                }
            }
        }
    }

};




int main() {

     SpaceShooter game(600,800);

     game.start();

}




