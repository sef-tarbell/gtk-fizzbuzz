//
// Created by sef on 6/18/20.
//

#include "DisplayWindow.h"

DisplayWindow::DisplayWindow()
    : _VBox(Gtk::ORIENTATION_VERTICAL),
      _buttonQuit("_Quit", true),
      _buttonFizzBuzz("FizzBuzz"),
      _buttonClearBuffer("Clear")
{
  set_title("FizzBuzz with GTK+");
  set_border_width(5);
  set_default_size(400, 200);

  // add the container
  add(_VBox);

  // add the TreeView, inside a ScrolledWindow, with the button underneath:
  _ScrolledWindow.add(_TextView);

  // only show the scrollbars when they are necessary:
  _ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  // set packing - used for the layout
  _VBox.pack_start(_ScrolledWindow);

  // add buttons:
  _VBox.pack_start(_buttonBox, Gtk::PACK_SHRINK);

  _buttonBox.pack_start(_buttonFizzBuzz, Gtk::PACK_SHRINK);
  _buttonBox.pack_start(_buttonClearBuffer, Gtk::PACK_SHRINK);
  _buttonBox.pack_start(_buttonQuit, Gtk::PACK_SHRINK);
  _buttonBox.set_border_width(5);
  _buttonBox.set_spacing(5);
  _buttonBox.set_layout(Gtk::BUTTONBOX_END);

  // connect signals:
  _buttonQuit.signal_clicked().connect(sigc::mem_fun(*this,
                                                     &DisplayWindow::onClickedQuit) );
  _buttonFizzBuzz.signal_clicked().connect(sigc::mem_fun(*this,
                                                         &DisplayWindow::onClickedFizzBuzz) );
  _buttonClearBuffer.signal_clicked().connect(sigc::mem_fun(*this,
                                                            &DisplayWindow::onClickedClear) );

  // create tag table and tags for text colors
  _refTagTable = Gtk::TextTagTable::create();
  createTag("blue text", Gdk::RGBA("#0000FF"));
  createTag("red text", Gdk::RGBA("#FF0000"));
  createTag("purple text", Gdk::RGBA("#FF00FF"));
  _refTextBuffer = Gtk::TextBuffer::create(_refTagTable);

  // set the text buffer into the view
  _TextView.set_buffer(_refTextBuffer);

  // let's go
  show_all_children();
}

DisplayWindow::~DisplayWindow() { }

void DisplayWindow::onClickedQuit()
{
  hide();
}

void DisplayWindow::onClickedFizzBuzz()
{
  // clear the text that is in the text view
  _refTextBuffer->set_text("");

  // get the position of line 1
  Gtk::TextIter pos = _refTextBuffer->get_iter_at_line(1);

  // iterate from 1 to 100
  for (int i = 1; i <= 100; ++i) {
    // multiples of 15 -> fizzbuzz in purple
    if (i % 15 == 0) {
      pos = _refTextBuffer->insert_with_tag(pos, "fizzbuzz\n", _tagMap["purple text"]);
    }
    // multiples of 5 -> buzz in red
    else if (i % 5 == 0) {
      pos = _refTextBuffer->insert_with_tag(pos, "buzz\n", _tagMap["red text"]);
    }
    // multiples of 3 -> fizz in blue
    else if (i % 3 == 0) {
      pos = _refTextBuffer->insert_with_tag(pos, "fizz\n", _tagMap["blue text"]);
    }
    // everything else display the number in default text
    else {
      pos = _refTextBuffer->insert(pos, Glib::ustring::format(i) + "\n");
    }
  }

  // set the buffer - is this unnecessary?
//  _TextView.set_buffer(_refTextBuffer);
}

void DisplayWindow::onClickedClear()
{
  // clear the text buffer
  _refTextBuffer->set_text("");
}

void DisplayWindow::createTag(Glib::ustring name, Gdk::RGBA color) {
  // create a tag
  Glib::RefPtr<Gtk::TextTag> tag = Gtk::TextTag::create(name);

  // set the foreground color
  tag->set_property("foreground-rgba", color);

  // add the tag into the tag table
  _refTagTable->add(tag);

  // add to the map, so we can retrieve the tag easily
  _tagMap[name] = tag;
}