return {
  "CRAG666/code_runner.nvim",
  event = "VeryLazy",
  dependencies = "nvim-lua/plenary.nvim",
  config = function()
    require("code_runner").setup({
      -- 將模式改為 "float" (浮動視窗)
      mode = "float", 
      
      -- 設定浮動視窗的外觀
      float = {
        -- 邊框樣式: "rounded" (圓角), "double" (雙線), "solid" (實線), "shadow" (陰影)
        border = "rounded", 
        
        -- 視窗大小與位置 (0~1 代表螢幕比例)
        height = 0.8, -- 佔高度 80%
        width = 0.8,  -- 佔寬度 80%
        x = 0.5,      -- 水平置中
        y = 0.5,      -- 垂直置中
        
        -- 背景透明度 (0~100, 100 為全透明)
        border_hl = "FloatBorder",
        float_hl = "Normal",
        blend = 0,
      },

      -- 這裡是你原本的語言執行設定
      filetype = {
        python = "python -u $dir/$fileName",
        cpp = "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir/$fileNameWithoutExt",
        javascript = "node $dir/$fileName",
        typescript = "deno run $dir/$fileName",
        rust = "cd $dir && rustc $fileName && $dir/$fileNameWithoutExt",
      },
    })
  end,
  keys = {
    { "<leader>r", ":RunCode<CR>", desc = "Run Code (Float)" },
    { "<leader>rf", ":RunFile<CR>", desc = "Run File" },
  },
}
