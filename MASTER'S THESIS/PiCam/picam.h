#ifndef PICAM_H
#define PICAM_H

#include <linux/videodev2.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <QMetaEnum>

class Picam : public QObject
{Q_OBJECT

private:
    struct v4l2_querymenu querymenu;
    struct v4l2_queryctrl queryctrl;
    struct v4l2_ext_controls queryext;
    struct v4l2_control control;
    char *dev;
    int fd;
public:
    enum colEffect {
        None = 0,
        BW = 1,
        Sepia = 2,
        Negative = 3,
        Emboss = 4,
        Sketch = 5,
        Sky_Blue = 6,
        Grass_Green = 7,
        Skin_Whiten = 8,
        Vivid = 9,
        Aqua = 10,
        Art_Freeze = 11,
        Silhouette = 12,
        Solarization = 13,
        Antique = 14,
    };
    Q_ENUMS(colEffect)
    colEffect getColEffects(int number) const { return colEffect(number); }
    Picam(char *device);
    int getAllSetings();
    int set(int controlID, int value);
    void enumerate_menu(void);
    virtual ~Picam();
};

#endif // PICAM_H
