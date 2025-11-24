
# build dir
BUILD_DIR := build
INCLUDE_DIR := include

# files
APP_BASIC := build/example_basic.out
APP_SRC_BASIC := example/example_basic.c
APP_OBJ_BASIC := build/example_basic.o

APP_ADVANCE := build/example_advance.out
APP_SRC_ADVANCE := example/example_advance.c
APP_OBJ_ADVANCE := build/example_advance.o

SRCS := src/pq.c
OBJS := build/pq.o

# compile flag
CFLAG := -I$(INCLUDE_DIR)
LDFLAG :=

all: $(APP_BASIC) $(APP_ADVANCE)

$(OBJS): $(SRCS) | $(BUILD_DIR)
	@gcc $(CFLAG) $< -c -o $@

$(APP_OBJ_BASIC): $(APP_SRC_BASIC) | $(BUILD_DIR)
	@gcc $(CFLAG) $< -c -o $@

$(APP_OBJ_ADVANCE): $(APP_SRC_ADVANCE) | $(BUILD_DIR)
	@gcc $(CFLAG) $< -c -o $@

$(APP_BASIC): $(OBJS) $(APP_OBJ_BASIC)
	@gcc $^ -o $@

$(APP_ADVANCE): $(OBJS) $(APP_OBJ_ADVANCE)
	@gcc $^ -o $@

run_example_basic: $(APP_BASIC)
	@./$<

run_example_advance: $(APP_ADVANCE)
	@./$<

clean:
	@rm -rf $(BUILD_DIR)

$(BUILD_DIR):
	@mkdir -p $@

# yung: $(APP) | $(BUILD_DIR)
# 	@printf "fuck you\n"