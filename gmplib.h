/* 定数宣言 */
#define MAX_IMAGESIZE 1280 /* 想定する縦・横の最大画素数 */
#define MAX_BRIGHTNESS 255 /* 想定する最大階調値 */
#define GRAYLEVEL 256 /* 想定する階調数(=最大階調値+1) */
#define MAX_FILENAME 256 /* 想定するファイル名の最大長 */
#define MAX_BUFFERSIZE 256 /* 利用するバッファ最大長 */
#define MAX_NUM_OF_IMAGES 5 /* 利用する画像の枚数 */
/* 大域変数の宣言 */
/* 画像データ image[n][x][y] */
unsigned char
image[MAX_NUM_OF_IMAGES][MAX_IMAGESIZE][MAX_IMAGESIZE];
/* image[n] の横幅・縦幅 */
int width[MAX_NUM_OF_IMAGES], height[MAX_NUM_OF_IMAGES];
/* 階調画像を入力する関数 */
void load_image( int n, char name[] )
/* n:画像番号，name[]:ファイル名（""のときはキーボード入力）*/
/* 横幅，縦幅はそれぞれ width[n], height[n] に代入する */
{
char file_name[MAX_FILENAME]; /* ファイル名用の文字配列 */
char buffer[MAX_BUFFERSIZE]; /* データ読み込み用作業変数 */
FILE *fp; /* ファイルポインタ */
int max_gray; /* 最大階調値 */
int x, y; /* ループ変数 */
/* 入力ファイルのオープン */
if ( name[0] == '¥0' ){
printf("入力ファイル名 (*.pgm) : ");
scanf("%s",file_name);
} else strcpy( file_name, name );
if ( (fp = fopen( file_name, "rb" ))==NULL ){
printf("その名前のファイルは存在しません．¥n");
exit(1);
}
/* ファイルタイプ(=P5)の確認 */
fgets( buffer, MAX_BUFFERSIZE, fp );
if ( buffer[0] != 'P' || buffer[1] != '5' ){
printf("ファイルのフォーマットが P5 とは異なります．¥n");
exit(1);
}
/* width[n], height[n] の代入（#から始まるコメントは読み飛ばす） */
width[n] = 0; height[n] = 0;
while ( width[n] == 0 || height[n] == 0 ){
fgets( buffer, MAX_BUFFERSIZE, fp );
if ( buffer[0] != '#' )
sscanf( buffer, "%d %d", &width[n], &height[n] );
}
/* max_gray の代入（#から始まるコメントは読み飛ばす） */
max_gray = 0;
while ( max_gray == 0 ){
fgets( buffer, MAX_BUFFERSIZE, fp );
if ( buffer[0] != '#' )
sscanf( buffer, "%d", &max_gray );
}
/* パラメータの画面への表示 */
printf("横の画素数 = %d, 縦の画素数 = %d¥n", width[n], height[n] );
printf("最大階調値 = %d¥n",max_gray);
if ( width[n] > MAX_IMAGESIZE || height[n] > MAX_IMAGESIZE ){
printf("想定値 %d x %d を超えています．¥n",
MAX_IMAGESIZE, MAX_IMAGESIZE);
printf("もう少し小さな画像を使って下さい．¥n");
exit(1);
}
if ( max_gray != MAX_BRIGHTNESS ){
printf("最大階調値が不適切です．¥n"); exit(1);
}
/* 画像データを読み込んで画像用配列に代入する */
for(y=0;y<height[n];y++)
for(x=0;x<width[n];x++)
image[n][x][y] = (unsigned char)fgetc( fp );
fclose(fp);
printf("画像は正常に読み込まれました．¥n");
