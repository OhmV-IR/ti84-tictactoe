enum class BlockState {
    OPEN = (int)'N',
    X = (int)'X',
    O = (int)'O',
};

enum class Winner {
    X = static_cast<int>(BlockState::X),
    O = static_cast<int>(BlockState::O),
    TIE,
    NONE
};