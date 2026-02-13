-- return {
--   "nvim-treesitter/nvim-treesitter",
--   event = { "BufReadPre", "BufNewFile" },
--   build = ":TSUpdate",
--   dependencies = {
--     "windwp/nvim-ts-autotag",
--   },
--   config = function()
--     -- import nvim-treesitter plugin
--     local treesitter = require("nvim-treesitter.configs")
--
--     -- configure treesitter
--     treesitter.setup({ -- enable syntax highlighting
--       highlight = {
--         enable = true,
--       },
--       -- enable indentation
--       indent = { enable = true },
--       -- enable autotagging (w/ nvim-ts-autotag plugin)
--       autotag = {
--         enable = true,
--       },
--       incremental_selection = {
--         enable = true,
--         keymaps = {
--           init_selection = "<C-space>",
--           node_incremental = "<C-space>",
--           scope_incremental = false,
--           node_decremental = "<bs>",
--         },
--       },
--     })
--   end,
-- }
--
return {
  "nvim-treesitter/nvim-treesitter",
  build = ":TSUpdate",
  event = { "BufReadPost", "BufNewFile" }, -- 懶加載，避免啟動時找不到路徑
  config = function()
    -- 使用 pcall 確保如果模組真的遺失，不會直接崩潰
    local status_ok, configs = pcall(require, "nvim-treesitter.configs")
    if not status_ok then
        return
    end

    configs.setup({
      ensure_installed = { "c", "lua", "vim", "vimdoc", "query", "python", "bash", "html", "markdown", "markdown_inline" },
      sync_install = false,
      highlight = {
        enable = true, -- 這會解決 render-markdown 的報錯
      },
      indent = {
        enable = true,
      },
    })
  end,
}
