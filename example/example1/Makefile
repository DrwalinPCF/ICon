
ROOT_PATH = ../../
include ../../Makefile


	
$(BDIR)/Server1.o: Server.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) $(INCLUDEPATHS)
server: $(BDIR)/Server1.o $(STATICLIB)
	$(CXX) -o Server.exe $^ $(CFLAGS) $(LIB) $(STATICLIB)

$(BDIR)/Client1.o: Client.cpp
	$(CXX) -c -o $@ $< $(CFLAGS) $(INCLUDEPATHS)
client: $(BDIR)/Client1.o $(STATICLIB)
	$(CXX) -o Client.exe $^ $(CFLAGS) $(LIB) $(STATICLIB)

all: server client


