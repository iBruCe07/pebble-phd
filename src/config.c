/*******************************
 * Config
 *******************************/

#include "main.h"
#include "appinfo.h"
#include "config.h"

static Config s_config = {
  .weather_enabled = false
};

static bool s_loaded = false;

static void store_persist(void) {
  persist_write_data(PERSIST_KEY_CONFIG, &s_config, sizeof(s_config));
  persist_write_int(PERSIST_KEY_STORAGE_VERSION, CONFIG_STORAGE_VERSION);
}

static void clear_persist(void) {
  persist_delete(PERSIST_KEY_CONFIG);
  persist_delete(PERSIST_KEY_STORAGE_VERSION);
}

static void read_current_persist(void) {
  if (persist_exists(PERSIST_KEY_CONFIG))
    persist_read_data(PERSIST_KEY_CONFIG, &s_config, sizeof(s_config));
}

static void migrate_persist(void) {
  uint32_t version = persist_read_int(PERSIST_KEY_STORAGE_VERSION); // defaults to 0 if key is missing.

  switch(version) {
    case 0:
      // Just delete this - perhaps we have multiple unversioned types, or 0 is just too
      // long ago to be worth handling.
      APP_LOG(APP_LOG_LEVEL_INFO, "Storage version is unset or too old, clearing it");
      clear_persist();
      break;
    // An example of how we would migrate an older version
    //case 1:  
      //read_v1_persist();
      //break;
    case CONFIG_STORAGE_VERSION:
      APP_LOG(APP_LOG_LEVEL_DEBUG, "Reading current storage");
      read_current_persist();
      break;
    default:
      // This is more recent than what we expect; we can't know what happened, so delete it
      APP_LOG(APP_LOG_LEVEL_INFO, "Storage version is unrecognised, clearing it");
      clear_persist();
      break;
  }
}

void config_init(void) {
  migrate_persist();
  s_loaded = true;
}

void config_deinit(void) {
  store_persist();
}

Config* config() {
  return &s_config;
}

bool config_is_loaded(void) {
  return s_loaded;
}
