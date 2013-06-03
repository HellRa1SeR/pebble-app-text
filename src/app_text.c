#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x9C, 0x89, 0x24, 0xE9, 0x1B, 0xBC, 0x45, 0x7A, 0xB9, 0x92, 0x63, 0x98, 0xB6, 0xF3, 0xFA, 0xD3 }
PBL_APP_INFO(MY_UUID,
             "Text App", "Mikulas",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;

TextLayer text_layer;

#define pageSize 3

int page = 0;
const char *texts[pageSize];
bool light = false;

void populateTexts()
{
  // GENERATE FROM texty.php

/* BEGINTEXT */
texts[0] = "Mi familia es muy importante en mi vida. Mi familia es italiana, y es muy grande y amorosa. Es bueno que tengo una familia que me ayuda. Mi papá y mi mamá me aman y me ayudan a pagar la escuela y los libros. Es increíble lo mucho que hacen por mí. No es posible que yo estaría muy bien sin ellos. Mi hermano me da consejos sobre la escuela y cómo vivir mi vida. Mi hermano es muy importante para mí. Mi hermana me da consejos sobre la escuela y el trabajo y las relaciones.";
texts[1] = "Ella es muy importante para mí. Mis abuelos me ayudan diciéndome experiencias que tuvieron en su vida. Es importante que estén en mi vida, porque he aprendido muchas lecciones de ellas. Mi padre es la persona más grande que conozco. Él ayuda a mantener mi familia para días feriados y vacaciones. No es posible que yo no puedo hablar con mi padre todos los días. Mi madre también me ama.";
texts[2] = "Ella me ayuda a aprender computación y lecciones de vida de las experiencias. Es increíble que tengo una gran familia en mi vida. Es bueno que me apoyan y me aman sin importar nada.";
/* ENDTEXT */

}

void drawPage(int id)
{
  text_layer_set_text(&text_layer, texts[page]);
}

void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;
  light = !light;
  light_enable(light);
}

void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  page = page < (pageSize - 1) ? page + 1 : 0;
  drawPage(page);
}

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
  (void)recognizer;
  (void)window;

  page = page > 0 ? page - 1 : (pageSize - 1);
  drawPage(page);
}


void config_provider(ClickConfig **config, Window *window) {
  (void)window;

  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;

  config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
  config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 400;

  config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
  config[BUTTON_ID_UP]->click.repeat_interval_ms = 400;
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
  window_set_fullscreen(&window, true);
  window_set_background_color(&window, GColorBlack);

  resource_init_current_app(&APP_RESOURCES);

  text_layer_init(&text_layer, window.layer.frame);
  text_layer_set_text_color(&text_layer, GColorWhite);
  text_layer_set_background_color(&text_layer, GColorClear);
  text_layer_set_font(&text_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_9)));
  layer_add_child(&window.layer, &text_layer.layer);

  populateTexts();
  drawPage(page);

  window_set_click_config_provider(&window, (ClickConfigProvider) config_provider);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
