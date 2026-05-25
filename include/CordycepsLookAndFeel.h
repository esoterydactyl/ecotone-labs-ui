#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class CordycepsLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CordycepsLookAndFeel();

    // ── Design token colours (used by components that need them) ──────────────
    static juce::Colour bg()         { return juce::Colour(0xff0E0C0F); }
    static juce::Colour bgWarm()     { return juce::Colour(0xff100E12); }
    static juce::Colour surface()    { return juce::Colour(0xff181519); }
    static juce::Colour surface2()   { return juce::Colour(0xff1F1B20); }
    static juce::Colour surface3()   { return juce::Colour(0xff25212A); }
    static juce::Colour hairline()   { return juce::Colour(0xff2C2730); }
    static juce::Colour hairlineHi() { return juce::Colour(0xff3A3340); }
    static juce::Colour textHi()     { return juce::Colour(0xffE9E2D4); }
    static juce::Colour textMid()    { return juce::Colour(0xff8F8A82); }
    static juce::Colour textDim()    { return juce::Colour(0xff5A554E); }
    static juce::Colour textGhost()  { return juce::Colour(0xff3C3833); }
    static juce::Colour cordy()      { return juce::Colour(0xffD67A3F); }
    static juce::Colour cordy2()     { return juce::Colour(0xffB05A28); }
    static juce::Colour alive()      { return juce::Colour(0xffA6C155); }
    static juce::Colour aliveDim()   { return juce::Colour(0xff6E8434); }
    static juce::Colour danger()     { return juce::Colour(0xffC44C3F); }
    static juce::Colour warn()       { return juce::Colour(0xffB8862E); }

    // ── Font helpers ──────────────────────────────────────────────────────────
    juce::Font makeMonoFont(float size, bool medium = false) const;
    juce::Font makeSerifFont(float size) const;

    // Static accessors — usable without a LookAndFeel instance (lazy-loaded).
    static juce::Font serifFont(float size);
    static juce::Font monoFont (float size, bool medium = false);

    // ── LookAndFeel overrides ─────────────────────────────────────────────────
    void drawButtonBackground(juce::Graphics&, juce::Button&,
                              const juce::Colour& backgroundColour,
                              bool highlighted, bool down) override;

    void drawButtonText(juce::Graphics&, juce::TextButton&,
                        bool highlighted, bool down) override;

    juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;

    void drawLinearSlider(juce::Graphics&, int x, int y, int width, int height,
                          float sliderPos, float minSliderPos, float maxSliderPos,
                          juce::Slider::SliderStyle, juce::Slider&) override;

    void drawTabButton(juce::TabBarButton&, juce::Graphics&,
                       bool isMouseOver, bool isMouseDown) override;

    void drawTabAreaBehindFrontButton(juce::TabbedButtonBar&, juce::Graphics&,
                                      int w, int h) override;

    void drawToggleButton(juce::Graphics&, juce::ToggleButton&,
                          bool highlighted, bool down) override;

    void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
                          float sliderPos, float startAngle, float endAngle,
                          juce::Slider&) override;

private:
    juce::Typeface::Ptr monoRegular;
    juce::Typeface::Ptr monoMedium;
    juce::Typeface::Ptr serifItalic;
};
