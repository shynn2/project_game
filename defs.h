#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60 // 초당 프레임 수
#define NUM_INGREDIENTS_MAX 100 // 화면에 존재할 수 있는 최대 재료/신발 수
#define GRAVITY 0.5 // 포물선 운동에 적용할 중력 가속도
#define MAX_SPEED 15.0 // 재료가 솟아오를 때의 최대 속도

#define PLAYER_LIVES 3 // 훠궈 닌자의 초기 목숨 수

// 재료/아이템의 종류
typedef enum {
    TYPE_BEEF,      // 득점 재료
    TYPE_CABBAGE,   // 득점 재료
    TYPE_TOFU,      // 득점 재료
    TYPE_SHOE       // 목숨을 잃는 아이템 (패널티)
} IngredientType;

// 프로그램 전체적으로 관리해야 하는 요소를 모아 놓은 구조체 [cite: 498]
typedef struct {
    SDL_Renderer *renderer; // 렌더링 관리를 위한 구조체 [cite: 501]
    SDL_Window *window;     // 창 관리를 위한 구조체 [cite: 502]
    TTF_Font *font;         // 폰트 관리를 위한 구조체 [cite: 503]
    
    // 마우스 입력 상태를 저장 (베기 시작점, 현재점)
    bool is_slicing;
    int mouse_x, mouse_y;
    // ... 다른 SDL 라이브러리 (Mixer 등) 요소 추가 가능

} App;

// 게임 내에서 움직이는 물체 (훠궈 재료, 신발)를 구현하기 위한 구조체
typedef struct {
    SDL_Texture *texture; // 텍스쳐 (그림파일) [cite: 532]
    SDL_Rect pos;         // 객체의 좌표, 위치, 너비, 높이를 저장하는 구조체 [cite: 533, 534]
    
    double v_x;           // x방향 속도벡터 [cite: 536]
    double v_y;           // y방향 속도벡터 (중력 적용) [cite: 537]
    double angle;         // 객체의 회전 각도 (선택 사항)

    IngredientType type;  // 재료의 종류 (고기, 신발 등)
    bool is_active;       // 현재 활성화되어 날아가는 중인지
    bool is_cut;          // 베였는지 여부
    
} Ingredient;

// 게임 내에 문자열을 표시할 경우 문자열을 나타내는 구조체 (스코어보드) [cite: 543]
typedef struct {
    SDL_Rect pos;       // 좌표와 위치 [cite: 550, 551]
    SDL_Color color;    // 글씨 색깔 [cite: 552]
    SDL_Surface *surface; // 폰트 렌더링을 위해 필요한 구조체 [cite: 553]
    SDL_Texture *texture; // 문자열을 저장한 텍스처 [cite: 554]
} Text;