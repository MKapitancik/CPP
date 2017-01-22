#include "picam.h"
#include <QDebug>

Picam::Picam(char *device)
{
    fd = open(device,O_NONBLOCK);
}

void Picam::enumerate_menu(){
    qDebug() << "Menu items:\n";

    memset (&querymenu, 0, sizeof (querymenu));
    querymenu.id = queryctrl.id;

    for (querymenu.index = queryctrl.minimum;
         querymenu.index <= queryctrl.maximum;
          querymenu.index++) {
        if (0 == ioctl (fd, VIDIOC_QUERYMENU, &querymenu)) {
            qDebug() <<  (char*)querymenu.name << endl;
        } else {
            perror ("VIDIOC_QUERYMENU");
            exit (EXIT_FAILURE);
        }
    }
}

int Picam::getAllSetings(){

    memset (&queryctrl, 0, sizeof (queryctrl));

    for (queryctrl.id = V4L2_CID_BASE;
         queryctrl.id < V4L2_CID_LASTP1;
         queryctrl.id++) {
        if (0 == ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl)) {
            if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
                continue;

            qDebug() << "Control " << (char*)queryctrl.name << endl;

            if (queryctrl.type == V4L2_CTRL_TYPE_MENU)
                enumerate_menu ();
        } else {
            if (errno == EINVAL)
                continue;

            perror ("VIDIOC_QUERYCTRL");
            exit (EXIT_FAILURE);
        }
    }

    for (queryctrl.id = V4L2_CID_PRIVATE_BASE;;
         queryctrl.id++) {
        if (0 == ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl)) {
            if (queryctrl.flags & V4L2_CTRL_FLAG_DISABLED)
                continue;

            qDebug() << "Control " << (char*)queryctrl.name << endl;

            if (queryctrl.type == V4L2_CTRL_TYPE_MENU)
                enumerate_menu ();
        } else {
            if (errno == EINVAL)
                break;

            perror ("VIDIOC_QUERYCTRL");
            exit (EXIT_FAILURE);
        }
    }
    struct v4l2_queryctrl qctrl;

    qDebug() << "Extended Controls" << endl;
    qctrl.id = V4L2_CTRL_FLAG_NEXT_CTRL;
    while (0 == ioctl (fd, VIDIOC_QUERYCTRL, &qctrl)) {
        qDebug() << "Control " << (char*)qctrl.name << endl;
        qctrl.id |= V4L2_CTRL_FLAG_NEXT_CTRL;
    }
    return 1;
}

int Picam::set(int controlID, int value){

    queryctrl.id = controlID;
  //  control.value = value;

    memset (&control, 0, sizeof (control));
    control.id = controlID;

    if (0 == ioctl (fd, VIDIOC_QUERYCTRL, &queryctrl)) {
        if((queryctrl.minimum <= value) & (queryctrl.maximum >= value) & !(value%queryctrl.step))
            if (0 == ioctl (fd, VIDIOC_G_CTRL, &control)) {
                control.value = value;

            /* The driver may clamp the value or return ERANGE, ignored here */

            if (-1 == ioctl (fd, VIDIOC_S_CTRL, &control)
                && errno != ERANGE) {
                perror ("VIDIOC_S_CTRL");
                exit (EXIT_FAILURE);
            }
        /* Ignore if is unsupported */
            } else if (errno != EINVAL) {
                perror ("VIDIOC_G_CTRL");
                exit (EXIT_FAILURE);
            }
    }
    else
        return 0;
    return 1;
}

Picam::~Picam(){
    close(fd);
}
