/*
 * DataParser.h - Library untuk parsing data string pada Arduino
 * Created by Claude And Command Prompt, Editing by Bekti, March 30, 2025
 */

#ifndef DataParser_h
#define DataParser_h

#include "Arduino.h"

class DataParser
{
public:
  /*
   * Memecah string input menjadi array string berdasarkan karakter pemisah
   *
   * @param input String input yang akan diparsing
   * @param outputData Array string untuk menyimpan hasil parsing
   * @param separator Karakter pemisah
   * @param stringCount Jumlah elemen array yang terisi setelah parsing
   */
  static void parse(String input, String *outputData, char separator, int &stringCount)
  {
    int indexData = 0;
    size_t indexChar = 0;

    // Reset jumlah string
    stringCount = 0;

    // Proses parsing string
    while (indexChar < input.length())
    {
      // Cek karakter pemisah
      if (input[indexChar] == separator)
      {
        indexData++;
        indexChar++;
      }
      else
      {
        // Tambahkan karakter ke array outputData
        outputData[indexData] += input[indexChar++];
      }

      // Update jumlah string
      if (indexData > stringCount)
      {
        stringCount = indexData;
      }
    }

    // Sesuaikan jumlah string (indeks dimulai dari 0)
    stringCount++;
  }
  /*
   * Splits an input string into an array of strings based on a separator character
   *
   * @param input Input string to be parsed
   * @param outputData Array of strings to store the parsing results
   * @param separator Separator character
   * @param stringCount Number of elements filled in the array after parsing
   * @param maxStrings Maximum number of strings to parse (array size limit)
   */
  static void parse(String input, String *outputData, char separator, int &stringCount, int maxStrings)
  {
    int dataIndex = 0;
    size_t charIndex = 0;

    // Reset string count
    stringCount = 0;

    // Process string parsing
    while (charIndex < input.length())
    {
      // Check for separator character
      if (input[charIndex] == separator)
      {
        dataIndex++;
        charIndex++;

        // Check if we've reached the maximum array size
        if (dataIndex >= maxStrings)
        {
          stringCount = maxStrings;
          Serial.println("RETURN: Maximum array size reached");
          return; // Exit function to prevent array overflow
        }
      }
      else
      {
        // Add character to outputData array
        outputData[dataIndex] += input[charIndex++];
      }

      // Update string count
      if (dataIndex > stringCount)
      {
        stringCount = dataIndex;
      }
    }

    // Adjust string count (index starts from 0)
    stringCount++;

    // Make sure we don't exceed the maximum array size
    if (stringCount > maxStrings)
    {
      Serial.println("RETURN: Limiting to maximum array size");

      stringCount = maxStrings;
    }
    Serial.println("Success Get data divided into " + (String)stringCount + " data strings");
  }
  static int count(String input, char separator)
  {
    int separatorCount = 0;
    size_t charIndex = 0;

    // Process string and count separators
    while (charIndex < input.length())
    {
      // Check for separator character
      if (input[charIndex] == separator)
      {
        separatorCount++;
      }
      charIndex++;
    }

    return separatorCount ;
  }
};

#endif
