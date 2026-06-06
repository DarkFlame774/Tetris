package com.abhinav.tetris.model;

import jakarta.persistence.*;
import lombok.*;

import java.time.LocalDateTime;

@Entity
@Table(name = "player")
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@Builder
public class Player {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(unique = true, nullable = false)
    private String playerName;

    @Column(nullable = false)
    private String hashPasswd;

    private LocalDateTime registeredAt;
    private LocalDateTime updatedAt;

}
