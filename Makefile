OBJECTS = main.o


all: inpainting


inpainting: $(OBJECTS)
	g++ -o inpainting $(OBJECTS) -lopencv_core -lopencv_highgui -lopencv_imgproc