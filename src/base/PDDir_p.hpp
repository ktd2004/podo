/* 
   Copyright 2011 PODO. 
   This file is part of PODO. 
   
   PODO is free software: you can redistribute it and/or modify 
   it under the terms of the GNU Lesser General Public License as  
   published by the Free Software Foundation, either version 3 of  
   the License, or (at your option) any later version. 
   
   PODO is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of 
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
   GNU Lesser General Public License for more details. 
   
   You should have received a copy of the GNU Lesser General Public  
   License along with PODO. If not, see <http://www.gnu.org/licenses/>. 
 */
#ifndef _PDDIR_P_H_
#define _PDDIR_P_H_

namespace PD {

class DirPrivate
{
public:
	std::string path;
	int filter;

public:
	DirPrivate(const char* p="")
	{
		path = p;
		filter = Dir::NoFilter;
	}

	String::StringList readDir(const char* dir, int filter, 
		std::string nameFilter)
	{
		String::StringList list;
		DIR *srcdir = opendir(dir);
		if(!srcdir)
		{
			//printf("Dir::readDir '%s' open failed!!", dir);
			return list;
		}
		struct dirent *pent;
		struct stat st;
		mode_t fileMode;	
		std::string allPath;

		while((pent = readdir(srcdir)) != NULL)
		{
			allPath = PD::String::format("%s/%s", dir,  pent->d_name);
			
			if(lstat(allPath.c_str(), &st) == -1)
			{
				//printf("Dir::readDir stat error\n");
				return list;
			}	
			fileMode = st.st_mode;

			bool add = false;
			// hidden file
			if( filter & Dir::Hidden )
			{
				if( pent->d_name[0] == '.' && strcmp(pent->d_name, ".") &&
					strcmp(pent->d_name, ".."))
					add = true;
			}
			// directory
			if( filter & Dir::Dirs )
			{
				if(S_ISDIR(fileMode)) add = true;
			}
			// no symbolic link file
			if( !(filter & Dir::NoSymLinks) ) 
			{	
				if (S_ISLNK(fileMode) ) add = true;
			}
			// symbolic file
			if( filter & Dir::SymLinks)
			{
				if (S_ISLNK(fileMode) ) add = true;		
			}

			// system
			if( filter & Dir::System )
			{
				if( S_ISFIFO(fileMode) || S_ISSOCK(fileMode) ) add = true;
			}
			// file
			if( filter & Dir::Files) 
			{
				if( !S_ISDIR(fileMode)) add = true;
			}
			// char device
			if( filter & Dir::CharDevice)
			{
				if( S_ISCHR(fileMode) ) add = true;
			}
			// block device
			if( filter & Dir::BlockDevice)
			{
				if( S_ISBLK(fileMode) ) add = true;
			}

			if(filter == Dir::NoFilter) add = true;

			if(add) 
			{
				if(nameFilter.length())
				{
					if(!strstr(pent->d_name, nameFilter.c_str())) continue;
				}
				list.push_back(pent->d_name);
			}
		}
		closedir(srcdir);
		return list;
	}


		
	off_t getDirFileSize (const char *directoryName)
	{
		//printf ("[Directory Name = %s]\n", directoryName);

		off_t retSize = 0;
		int fileType = 0;
		off_t fileSize = 0;
		char currentFilePath[1024];
		DIR *dirp;
		struct dirent *dp;

		dirp = opendir (directoryName);
		while (dirp) 
		{
			if ((dp = readdir (dirp)) != NULL)
			{
				if (!strcmp (".", dp->d_name)) 
					continue;
				if (!strcmp ("..", dp->d_name)) 
					continue;
				strcpy (currentFilePath, directoryName);
				strcat (currentFilePath, "/");
				strcat (currentFilePath, dp->d_name);

				fileType = getFileType (currentFilePath);
				if (Dir::RegularFile == fileType) 
				{
					retSize = getFileSize (currentFilePath);
					if( retSize == -1 )
						break;
					fileSize += retSize;
				}
				else if (Dir::DirectoryFile == fileType) 
					fileSize += getDirFileSize (currentFilePath);
			}
			else 
			{
				closedir (dirp);
				return fileSize;
			}
		}
		return fileSize;
	}

	int getFileType (const char *fileName)
	{
		struct stat buf;
		if (lstat (fileName, &buf)) 
		{
			//printf ("Dir::getFileType() lstat error.!!\n");
			return -1;
		}
		if (S_ISREG (buf.st_mode))
			return Dir::RegularFile;
		else if (S_ISDIR (buf.st_mode))
			return Dir::DirectoryFile;
		else
			return Dir::UnknownFile;
	}

	off_t getFileSize (const char *fileName)
	{
		struct stat buf;
		if (lstat (fileName, &buf)) 
		{
			//printf("Dir::getFileSize() lstat error.!!\n");
			return -1;
		}
		return buf.st_size;
	} 
};
} //namespace PD
#endif
