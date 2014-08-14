#pragma once
#include <string>
#include <map>
#include <fstream>

BEGIN_WIN32PP_NAMESPACE

typedef std::map<std::wstring, std::wstring> IniFileSection;
class IniFile : public std::map<std::wstring, IniFileSection>
{
public:

	IniFile()
	{ }

	IniFile(const std::wstring iniFilePath)
	{ 
		ReadFile(iniFilePath);
	}

	virtual ~IniFile()
	{ }


	void ReadFile(const std::wstring& iniFilePath)
	{
		std::wstring currentSection;
		std::wstring currentLine;
		int lineNumber = 0;

		std::wifstream inputFile(iniFilePath.c_str());
		if (inputFile.is_open())
		{
			this->clear();
			while (std::getline(inputFile, currentLine))
			{
				lineNumber++;
				std::wstring trimmedLine = TrimWhitespace(currentLine);
				if (IsCommentOrWhitespace(trimmedLine))
					continue;

				if (IsSectionHeader(trimmedLine))
				{
					currentSection = trimmedLine.substr(1, trimmedLine.size() - 1);
					continue;
				}

				size_t assignmentPosition = trimmedLine.find_first_of(AssignmentOperator);
				if (assignmentPosition == 0 || assignmentPosition == std::wstring::npos)
					throw std::exception("INI file syntax error on line: " + lineNumber);

				std::wstring key = TrimWhitespace(trimmedLine.substr(0, assignmentPosition - 1));
				std::wstring value = TrimWhitespace(trimmedLine.substr(assignmentPosition));
				this->at(currentSection)[key] = value;
			}
		}
	}

	void WriteFile(const std::wstring& iniFilePath)
	{
		std::wofstream outputFile(iniFilePath);
		if (outputFile.is_open())
		{
			for (IniFile::iterator iterSection = this->begin(); iterSection != this->end(); iterSection++)
			{
				const std::wstring& sectionName = iterSection->first;
				const IniFileSection& sectionKeyValues = iterSection->second;

				if (sectionKeyValues.size() > 0)
				{
					//write the section name to the file
					outputFile << SectionBeginOperator << sectionName << SectionEndOperator << std::endl;

					for (IniFileSection::const_iterator iterKeyValue = sectionKeyValues.begin(); iterKeyValue != sectionKeyValues.end(); iterKeyValue++)
					{
						//write current key/value pair
						outputFile << iterKeyValue->first << AssignmentOperator << iterKeyValue->second << std::endl;
					}
				}
			}
		}
	}

protected:
	const wchar_t AssignmentOperator = L'=';
	const wchar_t CommentOperator = L';';
	const wchar_t SectionBeginOperator = L'[';
	const wchar_t SectionEndOperator = L']';
	const std::wstring Whitespace = L" \t\r\n";

	bool IsCommentOrWhitespace(const std::wstring trimmedCurrentLine)
	{
		if (trimmedCurrentLine.size() == 0)
			return true;
		if (trimmedCurrentLine[0] == CommentOperator)
			return true;

		return false;
	}

	bool IsSectionHeader(const std::wstring trimmedCurrentLine)
	{

		if (trimmedCurrentLine[0] == SectionBeginOperator
			&& trimmedCurrentLine[trimmedCurrentLine.size() - 1] == SectionEndOperator)
			return true;

		return false;
	}

	std::wstring TrimWhitespace(const std::wstring& input)
	{
		std::wstring strResult = input;

		if (strResult.length() == 0)
			return strResult;

		// Trim from the left
		std::wstring::size_type nFirstNonWhitespace = strResult.find_first_not_of(Whitespace);
		if (nFirstNonWhitespace != std::wstring::npos)
		{
			strResult = strResult.substr(nFirstNonWhitespace, strResult.length() - nFirstNonWhitespace);
		}
		else
		{
			// This string has only white-space, so return a blank string
			strResult = std::wstring();
			return strResult;
		}

		// Trim from the right
		std::wstring::size_type nLastNonWhitespace = strResult.find_last_not_of(Whitespace);
		if (nLastNonWhitespace != std::wstring::npos)
		{
			strResult = strResult.substr(0, nLastNonWhitespace + 1);
		}

		return strResult;
	}
};

END_WIN32PP_NAMESPACE

