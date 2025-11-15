.PHONY: all test clean

GCC := g++

FLAGS := -I./include/ -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override \
-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast \
-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast \
-Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
-flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla \
-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr#-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

BUILD_DIR   := build
SRC_DIR     := src
INCLUDE_DIR := include
TEST_DIR    := tests

SRC_FILES       := $(SRC_DIR)/main.cpp
CACHE_OBJ_FILES := $(BUILD_DIR)/main.o
TESTS_OBJ_FILES := $(BUILD_DIR)/test.o
TEST_FILES      := $(TEST_DIR)/test.cpp

TARGET_CACHE := $(BUILD_DIR)/cache.out
TARGET_TEST  := $(BUILD_DIR)/test.out

all: cache

make_dir:
	@mkdir -p $(BUILD_DIR)

cache: make_dir $(TARGET_CACHE)

$(TARGET_CACHE): $(CACHE_OBJ_FILES)
	$(GCC) $(CACHE_OBJ_FILES) -o $@ $(FLAGS)


$(CACHE_OBJ_FILES): $(SRC_FILES) $(INCLUDE_DIR)/*.hpp
	$(GCC) $(FLAGS) -c $< -o $@

test: make_dir $(TARGET_TEST)
$(TARGET_TEST): $(TESTS_OBJ_FILES)
	$(GCC) $(TESTS_OBJ_FILES) -o $@ $(FLAGS) -lgtest -lgtest_main -pthread


$(TESTS_OBJ_FILES): $(TEST_FILES) $(INCLUDE_DIR)/*.hpp
	$(GCC) $(FLAGS) -lgtest -lgtest_main -pthread -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/*.out
