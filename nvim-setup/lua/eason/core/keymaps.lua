vim.g.mapleader = "/"

local keymap = vim.keymap

--general keymaps
keymap.set("n", "<leader>sv", "<C-w>v") -- split window vertically
keymap.set("n", "<leader>sh", "<C-w>s") -- split wndwos horizontally
keymap.set("n", "<leader>se", "<C-w>=") -- make split windows equal width
keymap.set("n", "<leader>sx", ":close<CR>") -- close current split window

keymap.set("n", "<leader>to", ":tabnew<CR>") --open new tab
keymap.set("n", "<leader>tx", ":tabclose<CR>") -- close current tab
keymap.set("n", "<leader>tn", ":tabclose<CR>") -- goto next tab
-- keymap.set("n", "<leader>tp", ":tabclose<CR>") -- goto prev tab
--
--plugin keymap
keymap.set("n", "<leader>sm", ":MaximizerToggle<CR>") -- allow split window maximize & restore to original

--nvime-tree
keymap.set("n", "<leader>e", ":NvimTreeToggle<CR>")

--telescope
keymap.set("n", "<leader>ff", "<cmd>Telescope find_files<cr>")
keymap.set("n", "<leader>fs", "<cmd>Telescope live_grep<cr>")
keymap.set("n", "<leader>fh", "<cmd>Telescope help_tags<cr>")
