/** 
 * @file button.h
 * @brief the EGE control:button
 * @author StudyC.cn@gmail.com
 * @date 2011-08-09
 */
#ifndef _EGE_BUTTON_H_
#define _EGE_BUTTON_H_

#ifndef _EGE_H_
#error include "button.h" must after include "ege.h" or "graphics.h"
#endif

#include "egecontrolbase.h"

#include <algorithm>

#ifdef DEBUG
#include "ege/label.h"
#else
#define logout(msg)
#endif

/**
 * @brief ��ť�ؼ�
 */
class button : public egeControlBase
{
    public:
        //overrides
        // ��Ļ���º�ᱻ���ã����ڸ����߼�
        // �����麯������Ҫֱ���໥����
        // ���º���������ط�0�����ӿؼ����ݼ��������Ϣ
        /**
         * @brief ��Ӧ�ո���س��İ���
         *
         * @param key
         * @param flag
         *
         * @return 0
         */
        virtual int  onKeyDown(int key, int flag) {
            if((key==13)||(key==32)){
                _pushed=true;
                redraw();
            }
            return 0; 
        }
        /**
         * @brief ��Ӧ�ո���س��ĵ���
         *
         * @param key
         * @param flag
         *
         * @return 0
         */
        virtual int  onKeyUp(int key, int flag) {
            if(((key==13)||(key==32))&&_pushed){
                if(_on_click){
                    if(!_on_click(callback_param)){
                        onClick();
                    }
                }else{
                    onClick();
                }
            }
            _pushed=false;
            redraw();
            return 0;
        }

        /**
         * @brief ��Ӧ���������
         *
         * @param x
         * @param y
         * @param flag
         *
         * @return 0
         */
        virtual int onMouse(int x, int y, int flag) {
            if((flag&mouse_flag_left)&&(flag&mouse_msg_down)){
                capmouse(true);
                _pushed=true;
                redraw();
            }else if((flag&mouse_flag_left)&&(flag&mouse_msg_up)){
                if(_pushed){
                    if(_on_click){
                        if(!_on_click(callback_param)){
                            onClick();
                        }
                    }else{
                        onClick();
                    }
                    capmouse(false);
                    _pushed=false;
                }
                redraw();
            }
            return 0; 
        }
        /**
         * @brief ��Ļ���º�ᱻ���ã����ڸ����߼�
         *
         * @return 0
         */
        virtual int  onUpdate() { 
            return 0;
        }
        /**
         * @brief ��Ҫ��ý���ʱ���ã�����ֵһ�㷵��0��ʾ��ȡ�������뽹�㣬���ط�0����������뽹��
         *
         * @return 0
         */
        virtual int  onGetFocus() {
            return 0;
        }
        /**
         * @brief ʧȥ���뽹��ʱ����
         */
        virtual void onLostFocus() {
            _pushed=false;
            redraw();
        }
        // ���óߴ�ǰ���ã��Զ�����������
        virtual void onSizing(int *w, int *h) {
            //egeControlBase::onSizing(w,h);
        }
        // ��Ӧ�ߴ�仯����
        virtual void onSize(int w, int h) {
            //egeControlBase::onSize(w,h);
            updatesidewidth();
            redraw();
        }
        // �ػ溯���������뻭��pimg�ϣ��Ա��ܿ��ƻ滭Ŀ��
        virtual void onDraw(PIMAGE pimg) const {
        }
        // �ߴ�仯ʱ���ã������ػ����˻���������
        virtual void onResetFilter() {
        }
        //virtual void onAddChild(egeControlBase* pChild) {}
        //virtual void onDelChild(egeControlBase* pChild) {}
        //virtual void onIdle() {} // �����ӿڣ�δ��
        // �������ϵĺ����������ж��壨ע������Ҫһ�£���Ҫ©��OnDraw���const��
        //init
        CTL_PREINIT(button, egeControlBase) {
            // do sth. before sub objects' construct function call
        } CTL_PREINITEND;
        button(CTL_DEFPARAM) : CTL_INITBASE(egeControlBase) {
            CTL_INIT; // must be the first line
            size(64, 32);
            _font_height = 12;
            strcpy(_face, "����");
            _line_color=BLACK;
            _bg_color=RGB(100,100,100);
            _text_color=BLACK;
            _shadow_color=RGB(50,50,50);
            updatesidewidth();

            _on_click=NULL;
            callback_param=NULL;
            _pushed=false;
            _alpha=0xff;
#ifdef DEBUG
            _logger=NULL;
#endif
            //redraw();
            //blendmode(true);
        }
        //member functions
        /**
         * @brief �ڻص�����ָ��ΪNULL��ص���������0ʱ������
         */
        virtual void onClick(){
        }
        /**
         * @brief �ػ�ؼ�
         */
        virtual void redraw() const {
            PushTarget targer(buf());
            setbkcolor_f(RED);
            setcolor(RED);
            cleardevice();
            setbkmode(TRANSPARENT);
            setfillstyle(_bg_color,SOLID_FILL);
            bar(0, 0, getw()-1, geth()-1);
            setfont(_font_height, 0, _face);
            setcolor(_text_color);

            //settextjustify(LEFT_TEXT,CENTER_TEXT);
            //outtextrect(_side_width, _side_width, getw()-_side_width, geth()-_side_width, _caption);
            //outtextrect(0, 0, getw(), geth(), _caption);
            int x=(getw()-textwidth(_caption))/2;
            int y=(geth()-textheight(_caption))/2;
            outtextxy(x,y,_caption);
            setbkcolor(_line_color);
            rectangle(0,0,getw(),geth());
            rectangle(_side_width,_side_width,getw()-_side_width,geth()-_side_width);
            setfillstyle(_shadow_color,SOLID_FILL);
            if(_pushed){
                int points[12]={
                    0,0,
                    getw()-1,0,
                    getw()-_side_width, _side_width-1,
                    _side_width-1,_side_width-1,
                    _side_width-1, geth()-_side_width-1,
                    0,geth()-1,
                };
                fillpoly(6,points);
            }else{
                int points[12]={
                    0,geth()-1,
                    _side_width-1,geth()-_side_width,
                    getw()-_side_width, geth()-_side_width,
                    getw()-_side_width, _side_width-1,
                    getw()-1,0,
                    getw()-1,geth()-1,
                };
                fillpoly(6,points);
            }
            line(getw()-_side_width, _side_width, getw(), 0);
            line(_side_width-1, geth()-_side_width, 0, geth());
            //line(getw()-_side_width, geth()-_side_width, getw(), geth());
            //line(0,0, _side_width, _side_width);
            setbkcolor_f(RGB(_alpha, _alpha, _alpha), filter());
            cleardevice(filter());
        }
        //attributes
        /**
         * @brief ����alphaֵ
         *
         * @param alpha 0x00 - 0xff
         */
        void alpha(int alpha){
            if(alpha<0){
                _alpha=0;
            }else if(alpha>0xff){
                _alpha=0xff;
            }else{
                _alpha=alpha;
            }
            if(_alpha<0xff){
                blendmode(true);
            }else{
                blendmode(false);
            }

        }
        /**
         * @brief ����alphaֵ
         *
         * @return alpha
         */
        int alpha() const{
            return _alpha;
        }
        /**
         * @brief ���ñ���ɫ
         *
         * @param color ����ɫ
         */
        void bgcolor(COLORREF color){
            _bg_color=color;
            redraw();
        }
        /**
         * @brief ���ر���ɫ
         *
         * @return ����ɫ
         */
        COLORREF bgcolor() const{
            return _bg_color;
        }
        /**
         * @brief ���ð�ť����ص�����
         *
         * @param fun �ص�����ָ�룬���ҽ�������ֵΪ0ʱ���Զ�����onClick
         * @param param ���Ӳ���������ԭ�����ݸ��ص�����
         */
        void callback(int (*fun)(void*),void* param){
            callback_param=param;
            _on_click=fun;
            redraw();
        }
        /**
         * @brief ���ػص�����ָ��
         *
         * @return �ص�����ָ�룻��δ���ã�����NULL
         */
        template <typename T>
            T callback() const{
                return _on_click;
            }
        /**
         * @brief �����ı�
         *
         * @param text �ı�
         */
        void caption(const char* text) {
            strcpy(_caption, text);
            redraw();
        }
        /**
         * @brief �����ı�
         *
         * @return �ı�
         */
        const char* caption() const{
            return _caption;
            //redraw();
        }
        /**
         * @brief ��������
         *
         * @param fontface ������
         */
        void font(const char* fontface) {
            strcpy(_face, fontface);
            redraw();
        }
        /**
         * @brief ��������
         *
         * @return ������
         */
        const char* font() const{
            return _face;
            //redraw();
        }
        /**
         * @brief ��������ߴ磬����
         *
         * @param height
         */
        void fontsize(int height) {
            _font_height = height;
            redraw();
        }
        /**
         * @brief ��������ߴ�
         *
         * @return ����ߴ�
         */
        int fontsize() const{
            return _font_height;
        }
        /**
         * @brief ���ð�ť��������ɫ
         *
         * @param color ��ɫ
         */
        void linecolor(COLORREF color){
            _line_color=color;
            redraw();
        }
        /**
         * @brief ���ذ�ť������ɫ
         *
         * @return ������ɫ
         */
        COLORREF linecolor() const{
            return _line_color;
        }
#ifdef DEBUG
        /**
         * @brief ���õ�����Ϣ����
         *
         * @param logger
         */
        void logger(label* logger){
            _logger=logger;
        }
        /**
         * @brief ���ص�����Ϣ����
         *
         * @return 
         */
        label* logger() const{
            return _logger;
        }
#endif
        /**
         * @brief ������Ӱ��ɫ
         *
         * @param color ��Ӱ��ɫ
         */
        void shadowcolor(COLORREF color){
            _shadow_color=color;
            redraw();
        }
        /**
         * @brief ������Ӱ��ɫ
         *
         * @return ��Ӱ��ɫ
         */
        COLORREF shadowcolor() const{
            return _shadow_color;
        }
        /**
         * @brief �����ı���ɫ
         *
         * @param color �ı���ɫ
         */
        void textcolor(COLORREF color){
            _text_color=color;
            redraw();
        }
        /**
         * @brief �����ı���ɫ
         *
         * @return �ı���ɫ
         */
        COLORREF textcolor() const{
            return _text_color;
        }
    protected:
        /**
         * @brief �����ߵĿ��
         */
        void updatesidewidth(){
            _side_width=std::min(geth(),getw())*0.2;
        }
#ifdef DEBUG
        /**
         * @brief ���������Ϣ
         *
         * @param msg ������Ϣ�ı�
         */
        void logout(const char* msg){
            if(_logger){
                _logger->setcaption(msg);
            }
        }
#endif
        bool _pushed;
        int (*_on_click)(void*);
        char _caption[1024];
        char _face[32];
        COLORREF _line_color;
        COLORREF _bg_color;
        COLORREF _text_color;
        COLORREF _shadow_color;
        int _side_width;
        int _font_height;
        int _alpha;
        void* callback_param;
#ifdef DEBUG
        label* _logger;
#endif
};

#endif /* _EGE_BUTTON_H_ */

