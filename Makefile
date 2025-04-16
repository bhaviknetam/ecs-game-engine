# OBJS specifies which files to compile as part of the project
OBJS = main.cpp AssetManager/AssetManager.cpp ECS/EntityManager.cpp Engine/Engine.cpp

# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# OBJ_NAME specifies the name of our executable
OBJ_NAME = ecs

# This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)