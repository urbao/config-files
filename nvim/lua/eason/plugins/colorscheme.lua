return {
  "rebelot/kanagawa.nvim",
  priority = 1000, -- 確保主題最先載入
  config = function()
    require("kanagawa").setup({
      -- 如果你喜歡透明背景 (像你之前的設定)，請設為 true
      transparent = true, 
      
      -- 這裡可以選擇不同的風格：
      -- "wave": 預設風格，深藍色背景 (最經典)
      -- "dragon": 黑色背景，對比度較高
      -- "lotus": 淺色背景 (Light mode)
      theme = "dragon", 
      
      -- 自訂背景顏色 (可選)
      overrides = function(colors)
        local theme = colors.theme
        return {
          -- 讓浮動視窗 (Floating Window) 的背景稍微暗一點，增加層次感
          NormalFloat = { bg = "none" },
          FloatBorder = { bg = "none" },
          FloatTitle = { bg = "none" },
          
          -- 讓 Pmenu (自動補全選單) 有更好的可視性
          Pmenu = { fg = theme.ui.shade0, bg = theme.ui.bg_p1 }, 
          PmenuSel = { fg = "NONE", bg = theme.ui.bg_p2 },
          PmenuSbar = { bg = theme.ui.bg_m1 },
          PmenuThumb = { bg = theme.ui.bg_p2 },
        }
      end,
    })

    -- 套用主題
    vim.cmd("colorscheme kanagawa")
  end,
}
