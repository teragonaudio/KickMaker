/*
 *  xmlWriter.h
 *  PluginCore
 *
 *  Created by Nik Reiman on 30.09.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __xmlWriter_H
#define __xmlWriter_H

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <stack>

#ifndef XML_WRITER_INDENT_SIZE
/*! Number of spaces to tab each embedded section */
/** \todo Indenting doesn't actually work yet.  Sorry, folks. */
#define XML_WRITER_INDENT_SIZE 0
#endif

#ifndef XML_WRITER_MAX_STRING
#define XML_WRITER_MAX_STRING 32
#endif

#if WIN32
#define snprintf _snprintf
#endif

enum DEF_XML_WRITER_MODES {
  XML_WRITER_MODE_APPEND,
  XML_WRITER_MODE_WRITE
};

class xmlWriter {
public:
  /*! \brief Create a new xmlLogger instance
  * \param path The absolute system path for the logfile.
  * \param mode Writing mode, see xmlWriter::DEF_XML_WRITER_MODES
  */
  xmlWriter(const char *path = NULL, int mode = XML_WRITER_MODE_APPEND);
  virtual ~xmlWriter();
  
  /*! \brief Close the current file */
  virtual bool closeFile();
  
  /*! \brief Close the current tag */
  virtual bool closeTag();
  
  /*! \brief Open a file for writing
  * \param path The full path of the filename to open
  * \param mode Either XML_WRITER_MODE_WRITE or XML_WRITER_MODE_APPEND
  */
  virtual bool openFile(const char *path, int mode = XML_WRITER_MODE_APPEND);
  
  /*! \brief Start a new tag
  * \param name The name of the tag
  */
  virtual bool openTag(char *name);
  
  /*! \brief Add an attribute to the current tag
  * \param attr The attribute name
  * \param value Value of the attribute
  */
  virtual bool writeTagAttr(char *attr, char *value);
  
  /*! \brief Add an attribute to the current tag
  * \param attr The attribute name
  * \param value Value of the attribute
  */
  virtual bool writeTagAttr(char *attr, float value);
  virtual bool writeTagAttr(char *attr, int value);
  virtual bool writeTagAttr(char *attr, long value);
  
  /*! \brief Write data within a tag
  * \param data Pointer to a block of data
  * \param size Number of bytes in data
  * \note This method will automatically close the tag after writing data
  */
  virtual bool writeTagData(void *data, long size);
  
protected:
  /*! A stack used to hold the list of parent tag names */
  std::stack<std::string> m_open_tags;
  /*! File pointer to the logfile */
  FILE *m_file_ptr;
  /*! Switch for checking to see if currently writing inside of a tag */
  bool m_in_tag;
  /*! \b Experimental */
  int m_indent_level;
  
private:
};

#endif