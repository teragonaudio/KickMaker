# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../Third-Party/vstsdk2.4 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0
  CXXFLAGS += $(CFLAGS) -I../../Third-Party/PluginParameters/include
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../Third-Party/vstsdk2.4 -I ../../JuceLibraryCode
  TARGET := KickMaker.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../Third-Party/vstsdk2.4 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -Os
  CXXFLAGS += $(CFLAGS) -I../../Third-Party/PluginParameters/include
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -shared -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../Third-Party/vstsdk2.4 -I ../../JuceLibraryCode
  TARGET := KickMaker.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/AdsrEnvelope_eb2c94c8.o \
  $(OBJDIR)/Compressor_70b8b09b.o \
  $(OBJDIR)/LopassFilter_c0b2a8c2.o \
  $(OBJDIR)/NoiseWave_2e84607b.o \
  $(OBJDIR)/SawtoothWave_48ad93da.o \
  $(OBJDIR)/SineWave_c102fa68.o \
  $(OBJDIR)/SquareWave_a5d35b8.o \
  $(OBJDIR)/TriangleWave_606ec63.o \
  $(OBJDIR)/Oscillator_8a6cfe29.o \
  $(OBJDIR)/PluginEditor_94d4fb09.o \
  $(OBJDIR)/PluginProcessor_a059e380.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_processors_44a134a2.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_PluginUtilities_e2e19a34.o \
  $(OBJDIR)/juce_VST_Wrapper_bb62e93d.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking KickMaker
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning KickMaker
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping KickMaker
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/AdsrEnvelope_eb2c94c8.o: ../../Source/Effects/AdsrEnvelope.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AdsrEnvelope.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Compressor_70b8b09b.o: ../../Source/Effects/Compressor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Compressor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LopassFilter_c0b2a8c2.o: ../../Source/Effects/LopassFilter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LopassFilter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NoiseWave_2e84607b.o: ../../Source/Waveforms/NoiseWave.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NoiseWave.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SawtoothWave_48ad93da.o: ../../Source/Waveforms/SawtoothWave.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SawtoothWave.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SineWave_c102fa68.o: ../../Source/Waveforms/SineWave.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SineWave.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SquareWave_a5d35b8.o: ../../Source/Waveforms/SquareWave.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SquareWave.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/TriangleWave_606ec63.o: ../../Source/Waveforms/TriangleWave.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling TriangleWave.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Oscillator_8a6cfe29.o: ../../Source/Oscillator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Oscillator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginEditor_94d4fb09.o: ../../Source/PluginEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PluginProcessor_a059e380.o: ../../Source/PluginProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: ../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_e2e19a34.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_bb62e93d.o: ../../JuceLibraryCode/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
