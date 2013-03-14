/*
 *  xmlWriter.cpp
 *  PluginCore
 *
 *  Created by Nik Reiman on 30.09.06.
 *  Copyright 2006 Teragon Audio. All rights reserved.
 *
 */

#ifndef __xmlWriter_H
#include "xmlWriter.h"
#endif

xmlWriter::xmlWriter(const char *path, int mode)
{
  m_file_ptr = NULL;
  m_in_tag = false;
  m_indent_level = 0;
  
  if(path) {
    openFile(path, mode);
  }
}

xmlWriter::~xmlWriter()
{
  closeFile();
}

bool xmlWriter::closeFile()
{
  /** Check to see if the file pointer is open, and if so, close it. */
  if(m_file_ptr)
  {
    fclose(m_file_ptr);
    return true;
  }
  else
  {
    return false;
  }
}

bool xmlWriter::closeTag()
{
  /** Algorithm: */
  /** If the tab level is less than 0, then return false. */
  if(m_indent_level < 0)
  {
    return false;
  }
  
  /** If the tag hasn't been closed, then do so. */
  if(m_in_tag)
  {
    fprintf(m_file_ptr, ">");
  }
  
  /** Print out the number of indent spaces multiplied by the current indent level. */
  for(int i = 0; i < m_indent_level * XML_WRITER_INDENT_SIZE; ++i)
  {
    fprintf(m_file_ptr, " ");
  }
  
  /** Write the closing tag element to file. */
  fprintf(m_file_ptr, "</%s>\n", (m_open_tags.top()).c_str());
  
  /** Decrease the tab level, pop the last tag off of the stack, and set the tag open switch to be false. */
  m_open_tags.pop();
  m_in_tag = false;
  return true;
}

bool xmlWriter::openFile(const char *path, int mode)
{
  /** Algorithm: */
  /** If the file already exists, then return false. */
  if(m_file_ptr)
  {
    return false;
  }
  
  /** Otherwise, open the actual file. */
  switch(mode)
  {
    case XML_WRITER_MODE_APPEND:
      m_file_ptr = fopen(path, "a");
      break;
    case XML_WRITER_MODE_WRITE:
      m_file_ptr = fopen(path, "w");
      break;
    default:
      return false;
  }
  
  /** Return the result of the open operation. */
  if(m_file_ptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool xmlWriter::openTag(char *name)
{
  /** Algorithm: */
  /** If no file is open, return false. */
  if(!m_file_ptr)
  {
    return false;
  }
  
  /** See if the tag is already open.  If so, then print a '\>' to close that tag and increase the indent level. */
  if(m_in_tag)
  {
    fprintf(m_file_ptr, ">");
    ++m_indent_level;
  }
  
  /** Print out the number of indent spaces multiplied by the current indent level. */
  for(int i = 0; i < m_indent_level * XML_WRITER_INDENT_SIZE; ++i)
  {
    fprintf(m_file_ptr, " ");
  }
  
  /** Write the tag header and flush the file pointer. */
  fprintf(m_file_ptr, "<%s ", name);
  m_in_tag = true;
  
  /** Push the tag name on the stack */
  m_open_tags.push(name);
  ++m_indent_level;
  return true;
}

bool xmlWriter::writeTagAttr(char *attr, char *value)
{
  /** Algorithm: */
  /** If not presently in a tag or given a valid file pointer, then return false. */
  if(!m_in_tag || !m_file_ptr)
  {
    return false;
  }
  
  /** Write the pair to file and flush the file pointer. */
  if(attr)
  {
    fprintf(m_file_ptr, "%s=\"%s\" ", attr, value);
    fflush(m_file_ptr);
  }
  return true;
}

bool xmlWriter::writeTagAttr(char *attr, float value)
{
  /** Use snprintf() to format a string and then call the other writeTagAttr(). */
  char vstr[XML_WRITER_MAX_STRING];
  snprintf(vstr, XML_WRITER_MAX_STRING, "%f", value);
  return writeTagAttr(attr, vstr);
}

bool xmlWriter::writeTagAttr(char *attr, long value)
{
  /** Use snprintf() to format a string and then call the other writeTagAttr(). */
  char vstr[XML_WRITER_MAX_STRING];
  snprintf(vstr, XML_WRITER_MAX_STRING, "%ld", value);
  return writeTagAttr(attr, vstr);  
}

bool xmlWriter::writeTagAttr(char *attr, int value)
{
  /** Use snprintf() to format a string and then call the other writeTagAttr(). */
  char vstr[XML_WRITER_MAX_STRING];
  snprintf(vstr, XML_WRITER_MAX_STRING, "%d", value);
  return writeTagAttr(attr, vstr);
}

bool xmlWriter::writeTagData(void *data, long size)
{
  /** Algorithm: */
  /** If not in a tag, or there is no open file pointer, then return false. */
  if(!m_in_tag || !m_file_ptr)
  {
    return false;
  }
  
  /** First close the current tag by manually writing a '\>' to file. */
  fprintf(m_file_ptr, ">");
  m_in_tag = false;
  
  /** Write the data block to file. */
  fwrite(data, size, 1, m_file_ptr);
  
  /** Close the tag. */
  return closeTag();
}