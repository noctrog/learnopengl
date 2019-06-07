include rules.mk

all: $(BINDIR)/$(PROJECT)

$(BINDIR)/$(PROJECT): $(CXX_OBJ) $(C_OBJ)
	@mkdir -p $(dir $@)
	$(CXX) $^ $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -rf $(BINDIR)/$(PROJECT)
