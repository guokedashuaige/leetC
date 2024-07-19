# 定义编译器
CC = gcc

# 定义编译选项 其中-g表示输出调试信息
CFLAGS = -Wall -O2 -g -std=c99

# 构建文件夹 编出来的会塞进里面
BUILD_DIR = build

# 定义目标文件
TARGET = ${BUILD_DIR}/generate_file

# 定义源文件
SRCS = main.c gennum.c

# 目标
all: $(TARGET)

# 定义目标文件依赖的对象文件
# OBJS = $(SRCS:.c=.o)
# 下面这句话使用 patsubst 函数将源文件列表中的每个 .c 文件名转换为对应的 .o 文件名，并放在 build 文件夹中
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(SRCS))

# 创建目标文件夹
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 目标文件的生成规则
#| $(BUILD_DIR): 这是一个 order-only 依赖项，它表示 $(TARGET) 对 $(BUILD_DIR) 目录的依赖，
# 但不会影响目标文件的重新构建。它确保在构建 $(TARGET) 之前，$(BUILD_DIR) 目录是存在的。
$(TARGET): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# .c 文件到 .o 文件的生成规则
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf ${BUILD_DIR} 

# make clean
.PHONY: all clean
