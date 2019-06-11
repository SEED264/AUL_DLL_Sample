#include <lua.hpp>

// ピクセルのデータを扱いやすくするための構造体
struct Pixel_RGBA {
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
};

// Luaから呼び出す関数
int mult_color(lua_State *L) {
    // 引数の受け取り
    Pixel_RGBA *pixels = reinterpret_cast<Pixel_RGBA*>(lua_touserdata(L, 1));
    int w = static_cast<int>(lua_tointeger(L, 2));
    int h = static_cast<int>(lua_tointeger(L, 3));
    double rm = lua_tonumber(L, 4);
    double gm = lua_tonumber(L, 5);
    double bm = lua_tonumber(L, 6);

    // forループで全ピクセルを処理
    // xが内側なのは横に操作した方がメモリの効率がよさそうだから
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int index = x + w * y;
            pixels[index].r *= rm;
            pixels[index].g *= gm;
            pixels[index].b *= bm;
        }
    }

    // 今回はLua側へ値を返さないので0を返す
    return 0;
}

// 関数のリスト
// 最後は両方にNULLかnullptrが入れられた要素を入れる
static luaL_Reg functions[] = {
    { "mult_color", mult_color },
    { nullptr, nullptr }
};

// モジュールの関数等の登録を行う関数
// Lua側からこの関数を探せるように、Cの関数として定義しなければならない
extern "C" {
__declspec(dllexport) int luaopen_AUL_DLL_Sample(lua_State *L) {
    luaL_register(L, "AUL_DLL_Sample", functions);
    return 1;
}
}