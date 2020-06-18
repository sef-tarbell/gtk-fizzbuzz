//
// Created by sef on 6/18/20.
//
#ifndef FIZZBUZZ_DISPLAYWINDOW_H
#define FIZZBUZZ_DISPLAYWINDOW_H

#include <gtkmm.h>

class DisplayWindow : public Gtk::Window
{
public:
    DisplayWindow();
    virtual ~DisplayWindow();

protected:
    // button signal handlers
    void onClickedQuit();
    void onClickedFizzBuzz();
    void onClickedClear();

    Gtk::Box _VBox;

    Gtk::ScrolledWindow _ScrolledWindow;
    Gtk::TextView _TextView;

    Glib::RefPtr<Gtk::TextBuffer> _refTextBuffer;
    Glib::RefPtr<Gtk::TextTagTable> _refTagTable;
    std::map<Glib::ustring, Glib::RefPtr<Gtk::TextTag>> _tagMap;

    Gtk::ButtonBox _buttonBox;
    Gtk::Button _buttonQuit;
    Gtk::Button _buttonFizzBuzz;
    Gtk::Button _buttonClearBuffer;

private:
    void createTag(Glib::ustring name, Gdk::RGBA color);
};

#endif //FIZZBUZZ_DISPLAYWINDOW_H
