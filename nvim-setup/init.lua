require("eason.plugins-setup")
require("eason.core.keymaps")
require("eason.core.options")
require("eason.core.colorscheme")
require("eason.plugins.nvim-tree")
require("eason.plugins.lualine")
require("eason.plugins.autopairs")
require("eason.plugins.treesitter")
require("eason.plugins.gitsigns")
require("eason.plugins.lspconfig")
require("eason.plugins.completion")
require("eason.plugins.telescope")

-- Cursor config
vim.api.nvim_set_hl(0, "Cursor_Insert", {fg='Grey7', bg='MediumSpringGreen' }) -- insert mode color
vim.api.nvim_set_hl(0, "Cursor_Normal", {fg='Grey7', bg='SteelBlue1'}) -- normal mode color
vim.api.nvim_set_hl(0, "Cursor_Visual", {fg='Grey7', bg='MediumOrchid'}) -- visual mode color
vim.api.nvim_set_hl(0, "Cursor_Command", {fg='Grey7', bg='Tan'}) -- command mode color
vim.opt.guicursor = 'n:block-Cursor_Normal,c-ci-cr:block-Cursor_Command,i-sm-o:block-Cursor_Insert,v-ve-r:block-Cursor_Visual,a:blinkon100'

