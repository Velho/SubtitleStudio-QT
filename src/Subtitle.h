#ifndef SUBTITLE_H
#define SUBTITLE_H

#include <QString>

/*!
 * \brief The Subtitle class
 * Abstraction of the subtitle table.
 * Style is not applied here.
 *
 * TODO This class will prop need refactoring when
 * new formats come into play.
 */
class Subtitle {
public:
    /*!
     * \brief Subtitle
     * Constructs the subtitle class.
     * \param idx
     * Index of the subtitle.
     * \param start
     * Start frame for the subtitle.
     * \param end
     * End frame for the subtitle.
     * \param t
     * The actual subtitle text.
     */
    Subtitle(int idx, int start, int end, QString t) :
        index{ idx }, startframe{ start }, endframe{ end }, text{ t }
    { }

    /*!
     * \brief getIndex
     * Index value(Unique, Primary).
     * \return
     * int index
     */
    int getIndex() const { return index; }
    /*!
     * \brief getStartFrame
     * Start frame.
     * \return
     * int startframe
     */
    int getStartFrame() const { return startframe; }
    /*!
     * \brief getEndFrame
     * End frame.
     * \return
     * int endframe
     */
    int getEndFrame() const { return endframe; }
    /*!
     * \brief getText
     * Subtitle text.
     * \return
     * std::string text;
     */
    QString getText() const { return text; }

private:
    int index;
    int startframe;
    int endframe;
    QString text;
};

#endif // SUBTITLE_H
