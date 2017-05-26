#include "qrencodepri.h"

void QrencodePri::paint(QPainter &painter)
{
    unsigned char *row, *p;
    int x, y;

    int symwidth = m_code->width + m_margin * 2;
    painter.setClipRect(QRect(0,0,symwidth, symwidth));
    painter.setPen(m_pen);
    painter.setBrush(m_fg);

    /* Make solid background */
    painter.fillRect(QRect(0, 0, symwidth, symwidth), m_bg);

    /* Write data */
    p = m_code->data;
    for(y=0; y<m_code->width; y++) {
        row = (p+(y*m_code->width));
        /* no RLE[翻译为游程编码，又译行程长度编码，又称变动长度编码法（run coding）] */
        for(x=0; x<m_code->width; x++) {
            if(*(row+x)&0x1) {
                painter.drawRect(m_margin + x, m_margin + y, 1, 1);
            }
        }

    }
}

QrencodePri::~QrencodePri()
{

}
