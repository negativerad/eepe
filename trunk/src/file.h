/*
 * Author - Erez Raviv <erezraviv@gmail.com>
 * 
 * Based on th9x -> http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef file_h
#define file_h


/// fileId of general file
#define FILE_GENERAL   0
/// convert model number 0..MAX_MODELS-1  int fileId
#define FILE_MODEL(n) (1+n)
#define FILE_TMP      (1+16)


#define ERR_NONE 0
#define ERR_FULL 1
#define ERR_TMO  2


class EFile
{
  uint8_t  m_fileId;    //index of file in directory = filename
  uint16_t m_pos;       //over all filepos
  uint8_t  m_currBlk;   //current block.id
  uint8_t  m_ofs;       //offset inside of the current block
  uint8_t  m_bRlc;      //control byte for run length decoder
  uint8_t  m_err;       //error reasons
  //uint16_t m_stopTime10ms; //maximum point of time for writing


  uint8_t eeprom[EESIZE];
  EeFs    *eeFs;

  //bool EeFsOpen();
  //int8_t EeFsck();
  //void EeFsFormat();
  //uint16_t EeFsGetFree();





  void eeprom_read_block (void *pointer_ram, uint16_t pointer_eeprom, size_t size);
  void eeWriteBlockCmp(void *i_pointer_ram, uint16_t i_pointer_eeprom, size_t size);
  uint8_t EeFsRead(uint8_t blk,uint8_t ofs);
  void EeFsWrite(uint8_t blk,uint8_t ofs,uint8_t val);
  uint8_t EeFsGetLink(uint8_t blk);
  void EeFsSetLink(uint8_t blk,uint8_t val);
  uint8_t EeFsGetDat(uint8_t blk,uint8_t ofs);
  void EeFsSetDat(uint8_t blk,uint8_t ofs,uint8_t*buf,uint8_t len);
  void EeFsFlushFreelist();
  void EeFsFlush();
  uint16_t EeFsGetFree();
  void EeFsFree(uint8_t blk);///free one or more blocks
  uint8_t EeFsAlloc(); ///alloc one block from freelist
  int8_t EeFsck();
  void EeFsFormat();
  bool EeFsOpen();




public:

  EFile();

  void load(void* buf);
  void save(void* buf);
  ///remove contents of given file
  void rm(uint8_t i_fileId);

  ///swap contents of file1 with them of file2
  void swap(uint8_t i_fileId1,uint8_t i_fileId2);

  ///return true if the file with given fileid exists
  bool exists(uint8_t i_fileId);

  ///open file for reading, no close necessary
  ///for writing use writeRlc() or create()
  uint8_t openRd(uint8_t i_fileId); 
  /// create a new file with given fileId, 
  /// !!! if this file already exists, then all blocks are reused
  /// and all contents will be overwritten.
  /// after writing closeTrunc has to be called
  void    create(uint8_t i_fileId, uint8_t typ);
  /// close file and truncate the blockchain if to long.
  void    closeTrunc();

  ///open file, write to file and close it. 
  ///If file existed before, then contents is overwritten. 
  ///If file was larger before, then unused blocks are freed
  uint16_t writeRlc(uint8_t i_fileId, uint8_t typ,uint8_t*buf,uint16_t i_len);

  uint8_t read(uint8_t*buf,uint16_t i_len);
  uint8_t write(uint8_t*buf,uint8_t i_len);

  ///return size of compressed file without block overhead
  uint16_t size(); 
  ///read from opened file and decode rlc-coded data
  uint16_t readRlc(uint8_t*buf,uint16_t i_len);





};

#endif
/*eof*/