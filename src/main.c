#include <pebble.h>
#include <analog.h>

static Window *s_main_window;

//static Layer *s_canvas_layer;
//static TextLayer *s_time_layer;
static GBitmap *s_bitmap;
static Layer *s_orbit_layer, *s_hands_layer;
static GPath *s_minute_arrow, *s_hour_arrow;

/* Initial code to display the Sisters and their charges as vectors, should I discover a working method of making the appropriate Pebble Draw Command (.pdc) files:
 static GDrawCommandImage *s_command_image;
 
 static void update_proc(Layer *layer, GContext *ctx) {
 // Place image in the center of the Window
 GSize img_size = gdraw_command_image_get_bounds_size(s_command_image);
 GRect bounds = layer_get_bounds(layer);
 
 const GEdgeInsets frame_insets = {
 .top = (bounds.size.h - img_size.h) / 2,
 .left = (bounds.size.w - img_size.w) / 2
 };
 
 // If the image was loaded successfully...
 if (s_command_image) {
 // Draw it
 gdraw_command_image_draw(ctx, s_command_image, grect_inset(bounds, frame_insets).origin);
 }
 }
 */

static void orbit_update_proc(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);
    
    // Get a tm structure
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    if(t->tm_hour <= 5 || t->tm_hour >= 18) window_set_background_color(s_main_window, GColorPictonBlue);
    else window_set_background_color(s_main_window, GColorOxfordBlue);
    
    if(s_bitmap) gbitmap_destroy(s_bitmap);
    
    // Decide which time-dependent watchface image to display
    if (t->tm_hour == 0 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE0);}
    else if (t->tm_hour == 0 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE2);}
    else if (t->tm_hour == 1 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE4);}
    else if (t->tm_hour == 1 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE6);}
    else if (t->tm_hour == 2 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE8);}
    else if (t->tm_hour == 2 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE10);}
    else if (t->tm_hour == 3 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE12);}
    else if (t->tm_hour == 3 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE14);}
    else if (t->tm_hour == 4 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE16);}
    else if (t->tm_hour == 4 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE18);}
    else if (t->tm_hour == 5 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE20);}
    else if (t->tm_hour == 5 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE22);}
    else if (t->tm_hour == 6 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE24);}
    else if (t->tm_hour == 6 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE26);}
    else if (t->tm_hour == 7 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE28);}
    else if (t->tm_hour == 7 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE30);}
    else if (t->tm_hour == 8 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE32);}
    else if (t->tm_hour == 8 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE34);}
    else if (t->tm_hour == 9 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE36);}
    else if (t->tm_hour == 9 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE38);}
    else if (t->tm_hour == 10 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE40);}
    else if (t->tm_hour == 10 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE42);}
    else if (t->tm_hour == 11 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE44);}
    else if (t->tm_hour == 11 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE46);}
    else if (t->tm_hour == 12 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE48);}
    else if (t->tm_hour == 12 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE50);}
    else if (t->tm_hour == 13 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE52);}
    else if (t->tm_hour == 13 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE54);}
    else if (t->tm_hour == 14 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE56);}
    else if (t->tm_hour == 14 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE58);}
    else if (t->tm_hour == 15 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE60);}
    else if (t->tm_hour == 15 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE62);}
    else if (t->tm_hour == 16 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE64);}
    else if (t->tm_hour == 16 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE66);}
    else if (t->tm_hour == 17 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE68);}
    else if (t->tm_hour == 17 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE70);}
    else if (t->tm_hour == 18 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE72);}
    else if (t->tm_hour == 18 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE74);}
    else if (t->tm_hour == 19 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE76);}
    else if (t->tm_hour == 19 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE78);}
    else if (t->tm_hour == 20 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE80);}
    else if (t->tm_hour == 20 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE82);}
    else if (t->tm_hour == 21 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE84);}
    else if (t->tm_hour == 21 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE86);}
    else if (t->tm_hour == 22 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE88);}
    else if (t->tm_hour == 22 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE90);}
    else if (t->tm_hour == 23 && t->tm_min >= 0 && t->tm_min <= 29) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE92);}
    else if (t->tm_hour == 23 && t->tm_min >= 30 && t->tm_min <= 59) {s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE94);}
    else {APP_LOG(APP_LOG_LEVEL_ERROR, "Time ERROR");}
    
    graphics_draw_bitmap_in_rect(ctx, s_bitmap, bounds);
}

static void hands_update_proc(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);
    
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    // minute/hour hand
    if (t->tm_hour <= 5 || t->tm_hour >=18) {
        graphics_context_set_fill_color(ctx, GColorOxfordBlue);
        graphics_context_set_stroke_color(ctx, GColorVividViolet);
    }
    else {
        graphics_context_set_fill_color(ctx, GColorIcterine);
        graphics_context_set_stroke_color(ctx, GColorChromeYellow);
    }
    
    gpath_rotate_to(s_minute_arrow, TRIG_MAX_ANGLE * t->tm_min / 60);
    gpath_draw_filled(ctx, s_minute_arrow);
    gpath_draw_outline(ctx, s_minute_arrow);
    
    gpath_rotate_to(s_hour_arrow, (TRIG_MAX_ANGLE * (((t->tm_hour % 12) * 6) + (t->tm_min / 10))) / (12 * 6));
    gpath_draw_filled(ctx, s_hour_arrow);
    gpath_draw_outline(ctx, s_hour_arrow);
    
    // dot in the middle
    if (t->tm_hour <= 5 || t->tm_hour >=18) {graphics_context_set_fill_color(ctx, GColorCobaltBlue);}
    else {
        graphics_context_set_fill_color(ctx, GColorPictonBlue);
    }
    graphics_fill_circle(ctx, GPoint(bounds.size.w / 2, bounds.size.h / 2), 2);
}

static void tick_handler(struct tm *t, TimeUnits units_changed) {
    layer_mark_dirty(window_get_root_layer(s_main_window));
}

static void window_load(Window *window) {
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);
    
    s_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CE0);
    
    s_orbit_layer = layer_create(bounds);
    layer_set_update_proc(s_orbit_layer, orbit_update_proc);
    layer_add_child(window_layer, s_orbit_layer);
    
    s_hands_layer = layer_create(bounds);
    layer_set_update_proc(s_hands_layer, hands_update_proc);
    layer_add_child(window_layer, s_hands_layer);
}

static void window_unload(Window *window) {
    gbitmap_destroy(s_bitmap);
    layer_destroy(s_orbit_layer);
    layer_destroy(s_hands_layer);
}

static void init() {
    // Set up main Window
    s_main_window = window_create();
    window_set_window_handlers(s_main_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    
    window_stack_push(s_main_window, true);
    
    // init hand paths
    s_minute_arrow = gpath_create(&MINUTE_HAND_POINTS);
    s_hour_arrow = gpath_create(&HOUR_HAND_POINTS);
    
    Layer *window_layer = window_get_root_layer(s_main_window);
    GRect bounds = layer_get_bounds(window_layer);
    GPoint center = grect_center_point(&bounds);
    gpath_move_to(s_minute_arrow, center);
    gpath_move_to(s_hour_arrow, center);
    
    // Register with TickTimerService
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
    gpath_destroy(s_minute_arrow);
    gpath_destroy(s_hour_arrow);
    
    tick_timer_service_unsubscribe();
    window_destroy(s_main_window);
}

int main() {
    init();
    app_event_loop();
    deinit();
}
