#include <drawlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int GetRandom(int min, int max);    //プロトタイプ宣言

int main(void)
{
	srand((unsigned)time(NULL));

    /* --- 変数宣言 --- */
    float wait_time = 0.003;

    /* プレイヤー */
    int p1_x = 245;
    int p2_x = 345;
    int p_y = 400;
    int p_w = 50;
    int p_h = 50;

    int ob_w = 50;
    int ob_h = 50;

    /* オブジェクトR1 */
    int obR1_x = 80;
    int obR1_y = 0;
    int obR1_vx;
    int obR1_vy;
    int obR1_c = 0; //衝突したか

    /* オブジェクトL1 */
    int obL1_x = 80;
    int obL1_y = 0;
    int obL1_vx;
    int obL1_vy;
    int obL1_c = 0; //衝突したか


    /* オブジェクト3 */

    /* スコア */
    int score = 0; 
    int sx = 600, sy = 50;
    char sscore[10];

    /* 制御関係の変数 */
    int start = 0;
    int t, k, x, y;

    dl_initialize(1.5);

    dl_stop();
    dl_clear(DL_C("black"));
    dl_text("PUSH 'F' to start", 180, 220, 1.0, DL_C("white"), 1);
    dl_resume();

    /* --- Fキーが押されるまで待機 --- */
    start = 0;

    while(start == 0)
    {
        /* Fキーが押されたら start を 1 にする */ 
        /* 入力キーの処理 */
        while (dl_get_event(&t, &k, &x, &y))
        {
            if (t == DL_EVENT_KEY)
            {
                if (k == 'f')
                { 
                    start = 1;
                }
            }
        }
        dl_wait(wait_time);
    }

    /* --- メインループ --- */
    while(1)
    {
        dl_get_event(&t, &k, &x, &y);
		
        if (k == 'd') p1_x = 145;
        if (k == 'f') p1_x = 245;
        if (k == 'j') p2_x = 345;
        if (k == 'k') p2_x = 445;

        /*x座標割り当て*/
        if(obR1_c == 1)
        {
            obR1_c = 0;
            switch (GetRandom(1,2))
            {
                case 1:
                    obR1_x = 145;
                    break;

                case 2:
                    obR1_x = 245;
                    break;

                default:
                    break;
            }
        }

        if(obL1_c == 1)
        {
            obL1_c = 0;
            switch (GetRandom(1,2))
            {
                case 1:
                    obL1_x = 345;
                    break;
                    
                case 2:
                    obL1_x = 445;
                    break;

                default:
                    break;
            }
        }

        obR1_y += 2;
        obL1_y += 2;

        /*画面外判定*/
        if (obR1_y > DL_HEIGHT)
        {
            obR1_c = 1;
            obR1_y = 0;
        }

        if (obL1_y > DL_HEIGHT)
        {
            obL1_c = 1;
            obL1_y = 0;
        }

        if (obL1_y + ob_h >= p_y && obL1_y <= p_y + p_h && obR1_x == p1_x) break;
        if (obR1_y + ob_h >= p_y && obR1_y <= p_y + p_h && obL1_x == p2_x) break;

        /* 描画処理 */
        dl_stop();
        dl_clear(DL_C("black"));
        //sprintf(sscore, "%5d", score);
        //dl_text(sscore, sx, sy, 1.0, DL_C("white"), 2);
        dl_rectangle(obR1_x, obR1_y, obR1_x + ob_w, obR1_y + ob_h, DL_C("white"), 1, 1);
        dl_rectangle(obL1_x, obL1_y, obL1_x + ob_w, obL1_y + ob_h, DL_C("white"), 1, 1);
        dl_rectangle(p1_x, p_y, p1_x + p_w, p_y + p_h, DL_C("red"), 1, 1);
        dl_rectangle(p2_x, p_y, p2_x + p_w, p_y + p_h, DL_C("red"), 1, 1);
        dl_resume();
        dl_wait(wait_time);
    }
    /* --- 終了画面の表示 --- */

    dl_stop();
    dl_clear(DL_C("black"));
    sprintf(sscore, "%5d", score);
    dl_text(sscore, sx, sy, 40, DL_C("white"), 2);
    dl_text("GAME OVER", 200, 220, 1.0, DL_C("white"), 1);
    dl_text("push 'F' to quit", 200, 300, 1.0, DL_C("white"), 1);
    dl_resume();

    /* --- Fキーが押されるまで待機 --- */
    /* 練習問題 開始画面と同じことをする */
    start = 0;
    while(start == 0)
    {
        /* Fキーが押されたら start を 1 にする */ 
        /* 入力キーの処理 */
        while (dl_get_event(&t, &k, &x, &y))
        {
            if (t == DL_EVENT_KEY)
            {
                if (k == 'f')
                { 
                    start = 1;
                }
            }
        }
        dl_wait(wait_time);
    }
    return 0;
}



//ランダム関数
int GetRandom(int min, int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}