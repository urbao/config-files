require("eason.core")
require("eason.lazy")

-- Cursor color configuration
vim.api.nvim_set_hl(0, "Cursor_Insert", {fg = 'Grey7', bg = 'MediumSpringGreen'})
vim.api.nvim_set_hl(0, "Cursor_Normal", {fg = 'Grey7', bg = 'SteelBlue1'})
vim.api.nvim_set_hl(0, "Cursor_Visual", {fg = 'Grey7', bg = 'MediumOrchid'})
vim.api.nvim_set_hl(0, "Cursor_Command", {fg = 'Grey7', bg = 'Tan'})
vim.opt.guicursor = 'n:block-Cursor_Normal,c-ci-cr:block-Cursor_Command,i-sm-o:ver40-Cursor_Insert,v-ve-r:block-Cursor_Visual,a:blinkon100'

-- make background transparent
vim.api.nvim_command(":hi Normal guibg=NONE")
