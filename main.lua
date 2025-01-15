#!/usr/bin/lua

local fs = require("fsystem")

-- ### TEST function : readdirFile

local tFiles = fs.readdirFile("./tests/")

for _, file in ipairs(tFiles) do print(file) end

-- ### TEST function : fileFormat

print(fs.fileFormat("./tests/fileCRLF.txt"))
print(fs.fileFormat("./tests/fileEMPTY.txt"))
print(fs.fileFormat("./tests/fileLF.txt"))
