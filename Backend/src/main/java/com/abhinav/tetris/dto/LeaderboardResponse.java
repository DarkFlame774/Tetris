package com.abhinav.tetris.dto;

import jakarta.validation.constraints.Size;

import java.util.List;

public record LeaderboardResponse(
        @Size(min = 3, max = 3)
        List<LeaderboardRankRepresentation> topPlayers,
        LeaderboardRankRepresentation currentPlayer
) {
}
