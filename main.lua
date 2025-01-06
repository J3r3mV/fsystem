#!/usr/bin/lua

local fs = require("fsystem")
local tFiles = fs.readdirFile("/home/jeremy")

for _, file in ipairs(tFiles) do print(file) end
