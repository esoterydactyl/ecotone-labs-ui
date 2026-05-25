#include "CordycepsLookAndFeel.h"
#include <EcotoneLabsUIFonts.h>

// ──────────────────────────────────────────────────────────────────────────────
// Constructor

CordycepsLookAndFeel::CordycepsLookAndFeel()
{
    // ── Load bundled fonts ────────────────────────────────────────────────────
    monoRegular = juce::Typeface::createSystemTypefaceFor(
        EcotoneLabsUIFonts::JetBrainsMonoRegular_ttf,
        EcotoneLabsUIFonts::JetBrainsMonoRegular_ttfSize);

    monoMedium = juce::Typeface::createSystemTypefaceFor(
        EcotoneLabsUIFonts::JetBrainsMonoMedium_ttf,
        EcotoneLabsUIFonts::JetBrainsMonoMedium_ttfSize);

    serifItalic = juce::Typeface::createSystemTypefaceFor(
        EcotoneLabsUIFonts::InstrumentSerifItalic_ttf,
        EcotoneLabsUIFonts::InstrumentSerifItalic_ttfSize);

    // ── Slider colours ────────────────────────────────────────────────────────
    // Per design spec the value box is borderless / transparent — just a
    // right-aligned mono readout sitting in the same row as the slider.
    setColour(juce::Slider::textBoxTextColourId,        textHi());
    setColour(juce::Slider::textBoxBackgroundColourId,  juce::Colours::transparentBlack);
    setColour(juce::Slider::textBoxOutlineColourId,     juce::Colours::transparentBlack);
    setColour(juce::Slider::textBoxHighlightColourId,   cordy().withAlpha(0.4f));

    // ── Label colours ─────────────────────────────────────────────────────────
    setColour(juce::Label::textColourId,                textMid());
    setColour(juce::Label::backgroundColourId,          juce::Colours::transparentBlack);

    // ── TextEditor colours ────────────────────────────────────────────────────
    setColour(juce::TextEditor::textColourId,            textHi());
    setColour(juce::TextEditor::backgroundColourId,      bgWarm());
    setColour(juce::TextEditor::outlineColourId,         hairline());
    setColour(juce::TextEditor::focusedOutlineColourId,  hairlineHi());
    setColour(juce::TextEditor::highlightColourId,       cordy().withAlpha(0.3f));
    setColour(juce::TextEditor::highlightedTextColourId, textHi());
    setColour(juce::CaretComponent::caretColourId,       cordy());

    // ── Scrollbar ─────────────────────────────────────────────────────────────
    setColour(juce::ScrollBar::thumbColourId,            hairlineHi());
    setColour(juce::ScrollBar::trackColourId,            bg());

    // ── PopupMenu ─────────────────────────────────────────────────────────────
    setColour(juce::PopupMenu::backgroundColourId,       surface());
    setColour(juce::PopupMenu::textColourId,             textMid());
    setColour(juce::PopupMenu::highlightedBackgroundColourId, surface2());
    setColour(juce::PopupMenu::highlightedTextColourId,  textHi());

    // ── ListBox (used by FileListComponent inside the file browser) ───────────
    setColour(juce::ListBox::backgroundColourId,         bgWarm());
    setColour(juce::ListBox::outlineColourId,            hairline());
    setColour(juce::ListBox::textColourId,               textMid());

    // ── File browser rows ─────────────────────────────────────────────────────
    setColour(juce::DirectoryContentsDisplayComponent::textColourId,
              textMid());
    setColour(juce::DirectoryContentsDisplayComponent::highlightColourId,
              cordy().withAlpha(0.18f));
    setColour(juce::DirectoryContentsDisplayComponent::highlightedTextColourId,
              textHi());

    // ── File chooser dialog (title bar, background) ───────────────────────────
    setColour(juce::FileChooserDialogBox::titleTextColourId, textHi());

    // ── Resizable window (the dialog box itself) ──────────────────────────────
    setColour(juce::ResizableWindow::backgroundColourId,     surface());

    // ── Alert / dialog windows ────────────────────────────────────────────────
    setColour(juce::AlertWindow::backgroundColourId,     surface());
    setColour(juce::AlertWindow::textColourId,           textMid());
    setColour(juce::AlertWindow::outlineColourId,        hairline());

    // ── ComboBox (used in the filter dropdown inside the file browser) ────────
    setColour(juce::ComboBox::backgroundColourId,        bgWarm());
    setColour(juce::ComboBox::textColourId,              textMid());
    setColour(juce::ComboBox::outlineColourId,           hairline());
    setColour(juce::ComboBox::arrowColourId,             textDim());
    setColour(juce::ComboBox::focusedOutlineColourId,    hairlineHi());

    // ── TextButton inside dialogs (OK / Cancel) ───────────────────────────────
    // Already covered by global TextButton colour logic above.

    // ── FilenameComponent (path bar in the file browser) ─────────────────────
    // Note: FilenameComponent doesn't declare colour IDs; it uses TextEditor internally.
    // TextEditor colours (set above) handle the path field appearance.
}

// ──────────────────────────────────────────────────────────────────────────────
// Font helpers

juce::Font CordycepsLookAndFeel::serifFont(float size)
{
    static juce::Typeface::Ptr tf = juce::Typeface::createSystemTypefaceFor(
        EcotoneLabsUIFonts::InstrumentSerifItalic_ttf,
        EcotoneLabsUIFonts::InstrumentSerifItalic_ttfSize);
    if (tf != nullptr)
        return juce::Font(tf).withHeight(size);
    return juce::Font(juce::FontOptions().withHeight(size).withStyle("Italic"));
}

juce::Font CordycepsLookAndFeel::monoFont(float size, bool medium)
{
    static juce::Typeface::Ptr regular = juce::Typeface::createSystemTypefaceFor(
        EcotoneLabsUIFonts::JetBrainsMonoRegular_ttf,
        EcotoneLabsUIFonts::JetBrainsMonoRegular_ttfSize);
    static juce::Typeface::Ptr med = juce::Typeface::createSystemTypefaceFor(
        EcotoneLabsUIFonts::JetBrainsMonoMedium_ttf,
        EcotoneLabsUIFonts::JetBrainsMonoMedium_ttfSize);
    auto tf = medium ? med : regular;
    if (tf != nullptr)
        return juce::Font(tf).withHeight(size);
    return juce::Font(juce::FontOptions(size));
}

juce::Font CordycepsLookAndFeel::makeMonoFont(float size, bool medium) const
{
    auto tf = medium ? monoMedium : monoRegular;
    if (tf != nullptr)
        return juce::Font(tf).withHeight(size);
    // Fallback
    return juce::Font(juce::FontOptions(size));
}

juce::Font CordycepsLookAndFeel::makeSerifFont(float size) const
{
    if (serifItalic != nullptr)
        return juce::Font(serifItalic).withHeight(size);
    return juce::Font(juce::FontOptions().withHeight(size).withStyle("Italic"));
}

// ──────────────────────────────────────────────────────────────────────────────
// Buttons

void CordycepsLookAndFeel::drawButtonBackground(
    juce::Graphics& g, juce::Button& button,
    const juce::Colour& /*backgroundColour*/,
    bool highlighted, bool down)
{
    auto bounds = button.getLocalBounds().toFloat().reduced(0.5f);

    const bool isDanger = (button.getProperties()["substrate-variant"].toString() == "danger");

    juce::Colour fill, border;

    if (isDanger)
    {
        // PANIC-style button: hairline rest, danger on hover.
        if (down)
        {
            fill   = danger().withAlpha(0.12f);
            border = danger();
        }
        else if (highlighted)
        {
            fill   = danger().withAlpha(0.06f);
            border = danger();
        }
        else
        {
            fill   = surface();
            border = hairline();
        }
    }
    else if (down)
    {
        fill   = surface3();
        border = hairlineHi();
    }
    else if (highlighted)
    {
        fill   = surface2();
        border = hairlineHi();
    }
    else
    {
        fill   = surface();
        border = hairline();
    }

    if (!button.isEnabled())
    {
        fill   = fill.withAlpha(0.45f);
        border = border.withAlpha(0.25f);
    }

    // Sharp corners — no radius
    g.setColour(fill);
    g.fillRect(bounds);
    g.setColour(border);
    g.drawRect(bounds, 1.0f);
}

void CordycepsLookAndFeel::drawButtonText(
    juce::Graphics& g, juce::TextButton& button,
    bool highlighted, bool /*down*/)
{
    const bool isDanger = (button.getProperties()["substrate-variant"].toString() == "danger");

    juce::Colour col;
    if (!button.isEnabled())
        col = textGhost();
    else if (isDanger)
        col = danger();
    else if (highlighted)
        col = textHi();
    else
        col = textMid();

    g.setColour(col);
    auto f = getTextButtonFont(button, button.getHeight());
    f.setExtraKerningFactor(0.12f);
    g.setFont(f);
    g.drawFittedText(button.getButtonText().toUpperCase(),
                     button.getLocalBounds().reduced(4, 2),
                     juce::Justification::centred, 1);
}

juce::Font CordycepsLookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
{
    return makeMonoFont(juce::jmin(15.75f, (float)buttonHeight * 0.9f), true);
}

// ──────────────────────────────────────────────────────────────────────────────
// Sliders

void CordycepsLookAndFeel::drawLinearSlider(
    juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float /*minSliderPos*/, float /*maxSliderPos*/,
    juce::Slider::SliderStyle style, juce::Slider& slider)
{
    if (style != juce::Slider::LinearHorizontal)
    {
        LookAndFeel_V4::drawLinearSlider(g, x, y, width, height,
                                          sliderPos, 0, 0, style, slider);
        return;
    }

    const float trackH = 1.0f;
    const float trackY = (float)y + ((float)height - trackH) * 0.5f;

    // Track background — hairline
    g.setColour(hairline());
    g.fillRect((float)x, trackY, (float)width, trackH);

    // Filled portion — cordy
    float fillW = sliderPos - (float)x;
    if (fillW > 0.0f)
    {
        g.setColour(cordy());
        g.fillRect((float)x, trackY, fillW, trackH);
    }

    // Diamond thumb (9×9 square rotated 45°)
    const float thumbSz = 9.0f;
    const float halfSz  = thumbSz * 0.5f;
    float cx = sliderPos;
    float cy = (float)y + (float)height * 0.5f;

    juce::Path diamond;
    diamond.addRectangle(-halfSz, -halfSz, thumbSz, thumbSz);

    juce::AffineTransform xform = juce::AffineTransform::rotation(
        juce::MathConstants<float>::pi * 0.25f).translated(cx, cy);

    g.setColour(textHi());
    g.fillPath(diamond, xform);
    g.setColour(cordy());
    g.strokePath(diamond, juce::PathStrokeType(1.0f), xform);
}

// ──────────────────────────────────────────────────────────────────────────────
// Tabs

void CordycepsLookAndFeel::drawTabButton(
    juce::TabBarButton& button, juce::Graphics& g,
    bool isMouseOver, bool /*isMouseDown*/)
{
    bool isFront = button.isFrontTab();
    auto bounds  = button.getLocalBounds().toFloat();

    juce::Colour fill = isFront         ? surface()
                        : isMouseOver   ? bgWarm()
                                        : bg();
    g.setColour(fill);
    g.fillRect(bounds);

    if (isFront)
    {
        g.setColour(cordy());
        g.fillRect(bounds.removeFromBottom(2.0f));
    }

    juce::Colour textCol = isFront       ? textHi()
                           : isMouseOver ? textMid()
                                         : textDim();
    g.setColour(textCol);
    auto f = makeMonoFont(15.75f);
    f.setExtraKerningFactor(0.22f);
    g.setFont(f);
    g.drawFittedText(button.getButtonText().toUpperCase(),
                     button.getLocalBounds().reduced(6, 0),
                     juce::Justification::centred, 1);
}

void CordycepsLookAndFeel::drawTabAreaBehindFrontButton(
    juce::TabbedButtonBar& bar, juce::Graphics& g, int w, int h)
{
    g.setColour(hairline());
    bool atTop = bar.getOrientation() == juce::TabbedButtonBar::TabsAtTop;
    if (atTop)
        g.fillRect(0, h - 1, w, 1);
    else
        g.fillRect(0, 0, w, 1);
}

// ──────────────────────────────────────────────────────────────────────────────
// Toggle button

void CordycepsLookAndFeel::drawToggleButton(
    juce::Graphics& g, juce::ToggleButton& button,
    bool highlighted, bool /*down*/)
{
    constexpr float pillW = 32.0f;
    constexpr float pillH = 16.0f;
    float ty   = ((float)button.getHeight() - pillH) * 0.5f;
    bool  on   = button.getToggleState();

    juce::Rectangle<float> pill(2.0f, ty, pillW, pillH);

    // Track — sharp corners
    g.setColour(on ? cordy().withAlpha(0.4f) : bgWarm());
    g.fillRect(pill);
    g.setColour(on ? cordy() : hairline());
    g.drawRect(pill, 1.0f);

    // Knob (small diamond)
    const float knobSz = 8.0f;
    float knobCX = on ? pill.getRight() - knobSz * 0.5f - 2.0f
                      : pill.getX() + knobSz * 0.5f + 2.0f;
    float knobCY = pill.getCentreY();

    juce::Path diamond;
    diamond.addRectangle(-knobSz * 0.4f, -knobSz * 0.4f, knobSz * 0.8f, knobSz * 0.8f);
    juce::AffineTransform xform = juce::AffineTransform::rotation(
        juce::MathConstants<float>::pi * 0.25f).translated(knobCX, knobCY);

    juce::Colour knobFill = highlighted ? textHi() : textMid();
    if (!button.isEnabled()) knobFill = knobFill.withAlpha(0.4f);
    g.setColour(knobFill);
    g.fillPath(diamond, xform);

    // Label
    g.setColour(button.isEnabled() ? textMid() : textGhost());
    g.setFont(makeMonoFont(11.0f));
    g.drawFittedText(button.getButtonText(),
                     (int)(pillW + 10.0f), 0,
                     button.getWidth() - (int)(pillW + 10), button.getHeight(),
                     juce::Justification::centredLeft, 1);
}

// ──────────────────────────────────────────────────────────────────────────────
// Rotary slider (pitch knob — stays circular per spec)

void CordycepsLookAndFeel::drawRotarySlider(
    juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float startAngle, float endAngle, juce::Slider&)
{
    float diameter = (float)juce::jmin(width, height) - 4.0f;
    float radius   = diameter * 0.5f;
    float cx       = (float)x + (float)width  * 0.5f;
    float cy       = (float)y + (float)height * 0.5f;

    // Body
    juce::Rectangle<float> body(cx - radius, cy - radius, diameter, diameter);
    g.setColour(surface());
    g.fillEllipse(body);
    g.setColour(hairline());
    g.drawEllipse(body.reduced(0.5f), 1.0f);

    // Track arc (full range, dim)
    const float trackR = radius - 3.5f;
    const float arcW   = 2.0f;
    juce::Path track;
    track.addArc(cx - trackR, cy - trackR, trackR * 2.0f, trackR * 2.0f,
                 startAngle, endAngle, true);
    g.setColour(hairline());
    g.strokePath(track, juce::PathStrokeType(arcW, juce::PathStrokeType::curved,
                                              juce::PathStrokeType::rounded));

    // Value arc — bi-directional from centre (zero semitones)
    float midAngle = startAngle + (endAngle - startAngle) * 0.5f;
    float curAngle = startAngle + sliderPos * (endAngle - startAngle);
    if (std::abs(curAngle - midAngle) > 0.02f)
    {
        juce::Path value;
        value.addArc(cx - trackR, cy - trackR, trackR * 2.0f, trackR * 2.0f,
                     juce::jmin(midAngle, curAngle),
                     juce::jmax(midAngle, curAngle), true);
        g.setColour(cordy());
        g.strokePath(value, juce::PathStrokeType(arcW, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::rounded));
    }

    // Indicator dot — small cordy circle
    float angle = curAngle - juce::MathConstants<float>::halfPi;
    float dotR  = 1.8f;
    float dotD  = trackR - arcW * 0.5f - 1.0f;
    g.setColour(cordy());
    g.fillEllipse(cx + dotD * std::cos(angle) - dotR,
                  cy + dotD * std::sin(angle) - dotR,
                  dotR * 2.0f, dotR * 2.0f);
}
