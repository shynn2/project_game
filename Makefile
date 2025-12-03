# 컴파일러 설정
CC = gcc

# 타겟 실행 파일 이름
TARGET = HuoguoChef

# 컴파일 옵션 (SDL2 설정 포함)
# -I src: src 폴더의 헤더 파일을 찾도록 설정
CFLAGS = `sdl2-config --cflags` -g -Wall -I src

# 링크 옵션 (SDL2 라이브러리 및 수학 라이브러리 링크)
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

# 소스 파일 목록 (src 폴더 내의 모든 .c 파일)
SRCS = $(wildcard src/*.c)

# 오브젝트 파일 목록 (src 폴더 내에 .o 파일 생성)
OBJS = $(SRCS:.c=.o)

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성 규칙
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

# .c 파일을 .o 파일로 컴파일하는 규칙
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# 청소 규칙
clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
