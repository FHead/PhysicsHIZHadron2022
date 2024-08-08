
default: Prepare TestRunCombine

Prepare:
	ln -sf $(ProjectBase)/BasicDistribution/20230605_DeltaPhiReproduction/ Root

TestRun: Execute
	./Execute

RunSystematics: Prepare Execute ExecuteCombine
	bash RunSystematics.sh

TestRunCombine: ExecuteCombine
	./ExecuteCombine

Execute: Harvest.cpp
	g++ Harvest.cpp -o Execute `root-config --cflags --libs` -I$(ProjectBase)/CommonCode/include/

ExecuteCombine: Combine.cpp
	g++ Combine.cpp -o ExecuteCombine `root-config --cflags --libs` -I$(ProjectBase)/CommonCode/include/


