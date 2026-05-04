#include "main.hpp"

#include "VivifyRuntime.hpp"
#include "custom-types/shared/register.hpp"

#include "scotland2/shared/modloader.h"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

Configuration &getConfig() {
  static Configuration config(modInfo);
  return config;
}

MOD_EXTERN_FUNC void setup(CModInfo *info) noexcept {
  *info = modInfo.to_c();

  getConfig().Load();

  Paper::Logger::RegisterFileContextId(PaperLogger.tag);

  PaperLogger.info("Completed setup!");
}

MOD_EXTERN_FUNC void late_load() noexcept {
  il2cpp_functions::Init();

  PaperLogger.info("Registering custom types...");
  custom_types::Register::AutoRegister();

  PaperLogger.info("Starting Vivify...");
  Vivify::LateLoad();
  PaperLogger.info("Vivify loaded successfully!");
}

