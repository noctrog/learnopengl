PROJECT = learnopengl

SRCDIR 		 = src
INCDIR 		 = include
BINDIR 		 = bin
OBJDIR		 = obj

CFLAGS		 = 
CXXFLAGS	+= --std=c++14 -g
LDFLAGS		+= -ldl -lGL -lSDL2 -lassimp
INCLUDE 	+= -I$(INCDIR) -I$(INCDIR)/glad -I$(INCDIR)/KHR

CXX_SRC		 = $(wildcard $(SRCDIR)/*.cpp)
CXX_OBJ		 = $(addprefix $(OBJDIR)/,$(notdir $(CXX_SRC:.cpp=.o)))
C_SRC		 = $(wildcard $(SRCDIR)/*.c)
C_OBJ		 = $(addprefix $(OBJDIR)/,$(notdir $(C_SRC:.c=.o)))

CC		 = gcc
CXX		 = g++
